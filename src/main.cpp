#include "luau-parser.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char **argv)
{
	po::options_description desc("Available options");

	long min;
	long max;

	desc.add_options()("help,h", "produce help message")("min", po::value<long>(&min)->default_value(-200), "smallest supported number")("max", po::value<long>(&max)->default_value(200), "largest supported number");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << "\n";
		return 1;
	}

	LuauParser parser("template.luau", min, max);

	parser.write();
	parser.close();

	return 0;
}
