#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "obj_scanner.h"
#include "obj_parser.h"

namespace utility
{
    class obj_reader
    {
    public:
        obj_reader(const std::string &filename, bool trace_scanning = false, bool trace_parsing = false);
        ~obj_reader();

    public:
        bool read();
        int yylex(obj_parser::semantic_type *lval, obj_parser::location_type *loc);
        void error(const obj_parser::location_type &loc, const std::string &msg);
    
    private:
        bool _trace_scanning;
        bool _trace_parsing;
        bool _error;
        std::string _filename;

        obj_parser _parser;
        obj_scanner _scanner;
    };

    inline void obj_reader::error(const obj_parser::location_type &loc, const std::string &msg)
    {
        _error = true;
        std::cerr << loc << ":" << msg;
    }

    inline int obj_reader::yylex(obj_parser::semantic_type *lval, obj_parser::location_type *loc)
    {
        return _scanner.yylex(lval, loc);
    }
}
