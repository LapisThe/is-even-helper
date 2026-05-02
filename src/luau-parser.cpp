#include "luau-parser.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

LuauParser::LuauParser(const std::string &file, const std::string &output, long min, long max) : _min(min), _max(max)
{
	_inStream.open(file, std::ios::in);

	if (_inStream.fail())
	{
		switch (errno)
		{
		case EACCES:
			std::cout << "No permission to read template file\n";
			break;

		case ENOENT:
			std::cout << "No template file found\n";
			break;

		default:
			std::perror("opening template file");
		}

		exit(EXIT_FAILURE);
	}

	_outStream.open(output, std::ios::out);

	if (_outStream.fail())
	{
		switch (errno)
		{
		case EACCES:
			std::cout << "No permission to write to output file\n";
			break;

		default:
			std::perror("opening output file");
		}

		exit(EXIT_FAILURE);
	}
}

std::streampos LuauParser::find_placeholder()
{
	return find_placeholder(_inStream.tellg());
}

std::streampos LuauParser::find_placeholder(std::streampos start)
{
	_inStream.seekg(start);

	std::string line;

	while (std::getline(_inStream, line, '['))
	{
		// Move the pointer to the supposed closing bracket
		_inStream.seekg(1, std::fstream::cur);

		char closer = _inStream.peek();

		// Move the pointer to the delimiter
		_inStream.seekg(-2, std::fstream::cur);

		if (closer != ']')
		{
			return -1;
		}

		return _inStream.tellg();
	}

	return -1;
}

void LuauParser::write_from_instream(std::streampos readStart, std::streampos readEnd)
{
	_inStream.seekg(readStart);

	size_t bufferSize = readEnd - readStart;
	char *buffer = new char[bufferSize];

	_inStream.read(buffer, bufferSize);
	_outStream.write(buffer, bufferSize);

	delete[] buffer;
}

void LuauParser::write()
{
	std::streampos placeholder(0);

	for (;;)
	{
		std::streampos readStart;

		if (placeholder == 0)
		{
			readStart = std::move(placeholder);
		}
		else
		{
			// Move the read pointer ahead of the closing placeholder bracket
			readStart = std::move(placeholder) + std::streampos(3);
		}

		placeholder = find_placeholder(readStart);

		if (placeholder == -1)
		{
			_inStream.seekg(readStart);

			std::string line;

			while (std::getline(_inStream, line))
			{
				_outStream << line << "\n";
			}
			break;
		}

		_inStream.seekg(1, std::fstream::cur);

		char placeholderNo = _inStream.peek();

		std::string content = "";

		switch (placeholderNo)
		{
		case '1':
		{
			content = std::to_string(_min);
			break;
		}

		case '2':
		{
			content = std::to_string(_max);
			break;
		}

		case '3':
		{
			write_from_instream(readStart, placeholder);

			for (long i = _min; i <= _max; i++)
			{
				content = "\tif PassedNumber == " + std::to_string(i) + " then\n\t\treturn " + (i % 2 == 0 ? "true" : "false") + "\n\tend\n";

				// Remove first \t
				if (i == _min)
				{
					content.erase(0, 1);
				}

				// Remove trailing \n
				if (i == _max)
				{
					content.pop_back();
				}

				_outStream.write(content.c_str(), content.size());
			}
			continue;
		}

		default:
		{
			throw std::runtime_error("invalid placeholder number in template.luau");
		}
		}

		write_from_instream(readStart, placeholder);

		_outStream.write(content.c_str(), content.size());
	}

	_outStream.flush();
}

void LuauParser::close()
{
	_inStream.close();
	_outStream.close();
}
