#include "obj_reader.h"
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
/*
	obj_scanner scanner(filename);
	obj_parser parser(scanner);
	auto t0 = high_resolution_clock::now();
	parser.parse();
	auto t = high_resolution_clock::now() - t0;
	auto dur = duration_cast<milliseconds>(t).count();
	std::cout << "lines: " << scanner.lineno() << std::endl;
	std::cout << "time used: " << dur / 1000.0 << "s" << std::endl;
*/

    auto t0 = high_resolution_clock::now();
    obj_reader r(filename);
    r.read();
    auto t = high_resolution_clock::now() - t0;
    auto dur = duration_cast<milliseconds>(t).count();

    std::cout << "objects: " << r.objects().size() << std::endl;
    std::cout << "faces: " << r.faces().size() << std::endl;
    std::cout << "vertices: " << r.vertices().size() << std::endl;
    std::cout << "textures: " << r.textures().size() << std::endl;
    std::cout << "normals: " << r.normals().size() << std::endl;
	std::cout << "materials: " << r.materials().size() << std::endl;

    for(auto o : r.objects())
    {
        std::cout << "object: " << (o->name ? (*o->name) : "") << ", faces: " << o->faces.size() << std::endl;
    }

    for(auto m : r.materials())
    {
        std::cout << "material: " << (m.first ? (*m.first) : "") << std::endl;
    }

    std::cout << "time used: " << dur / 1000.0 << "s" << std::endl;
    return 0;
}
