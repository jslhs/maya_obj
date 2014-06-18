#include "obj_reader.h"

namespace utility{

obj_reader::obj_reader(const std::string &filename, bool trace_scanning, bool trace_parsing)
    : _filename(filename)
    , _error(false)
    , _trace_scanning(trace_scanning)
    , _trace_parsing(trace_parsing)
    , _scanner(filename)
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
    _parser.parse();
    return _error;
}

}
