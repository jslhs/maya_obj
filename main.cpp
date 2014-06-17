#include "obj_scanner.h"
#include "obj_parser.h"
#include <chrono>

int main(int argc, char *argv[])
{
	using namespace utility;
	using namespace std;
	using namespace chrono;
	std::string filename;
	if(argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		std::cout << "obj file: ";
		std::cin >> filename;
	}

	obj_scanner scanner(filename);
	obj_parser parser(scanner);
	auto t0 = high_resolution_clock::now();
	parser.parse();
	auto t = high_resolution_clock::now() - t0;
	auto dur = duration_cast<milliseconds>(t).count();
	std::cout << "lines: " << scanner.lineno() << std::endl;
	std::cout << "time used: " << dur / 1000.0 << "s" << std::endl;
	return 0;
}
