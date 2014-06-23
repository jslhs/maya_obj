#include "obj_reader.h"

namespace utility{

obj_reader::obj_reader(const std::string &filename, bool trace_scanning, bool trace_parsing)
    : _obj_filename(filename)
    , _error(false)
    , _trace_scanning(trace_scanning)
    , _trace_parsing(trace_parsing)
    , _parser(*this)
    , _obj(nullptr)
    , _mtl(nullptr)
{

}

obj_reader::~obj_reader()
{
}

bool obj_reader::read()
{
	_parser.set_debug_level(_trace_parsing);
	_obj_fs.open(_obj_filename);
	if(_obj_fs.fail())
	{
		std::cerr << "unable to open file: " << _obj_filename << std::endl;
		return false;
	}
    _scanner.scan(&_obj_fs, &_obj_filename);
	if(_parser.parse()) return false;
    if(!_mtl_filename.empty())
    {
	    _mtl_fs.open(_mtl_filename);
	    if(_mtl_fs.fail())
    	{
		    std::cerr << "unable to open file: " << _mtl_filename << std::endl;
		    return false;
	    }
	    _scanner.scan(&_mtl_fs, &_mtl_filename);
    }
    return !_parser.parse();
}

void obj_reader::parse_mtl(const std::string &filename)
{
	_mtl_filename = filename;
}

}
