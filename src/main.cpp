#include "luau-parser.hpp"

int main(int argc, char **argv)
{
	LuauParser parser("template.luau", -1000000l, 1000000l);

	parser.write();
	parser.close();

	return 0;
}
