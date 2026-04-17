#pragma once

#include <fstream>
#include <string>

class LuauParser
{
	std::ifstream _inStream;
	std::ofstream _outStream;

	long _min;
	long _max;

	/**
	 * @return starting from the current stream's read pointer, the stream position of the first opening placeholder bracket found
	 */
	std::streampos get_placeholder();
	/**
	 * @param start - where to start looking for the opening placeholder bracket
	 * @return stream position of the first opening placeholder bracket found
	 */
	std::streampos get_placeholder(std::streampos start);
	/**
	 * @param readStart - template file read start pointer
	 * @param readEnd - template file read end pointer
	 * @param writeStart - output file write start pointer
	 * @param buff - string to write to output file
	 */
	void write(std::streampos readStart, std::streampos readEnd, std::streampos writeStart, const std::string &buff);

public:
	LuauParser(const std::string &file, long min, long max);

	void write();
	void close();
};
