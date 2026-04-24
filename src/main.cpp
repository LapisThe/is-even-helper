#include "luau-parser.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char **argv)
{
	po::options_description desc("Available options");

	std::string input;
	std::string output;
	long min;
	long max;

	desc.add_options()("help,h", "produce help message")("input,i", po::value<std::string>(&input)->default_value("template.luau"), "input file (template) path")("output,o", po::value<std::string>(&output)->default_value("IsEven.luau"), "output file path")("max", po::value<long>(&max)->default_value(200), "largest supported number")("min", po::value<long>(&min)->default_value(-200), "smallest supported number");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << "\n";
		return 1;
	}

	LuauParser parser(input, output, min, max);

	parser.write();
	parser.close();

	return 0;
}
