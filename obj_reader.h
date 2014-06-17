#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "obj_parser.h"

namespace utility
{
    namespace obj
    {
        class face;
        class vertex;
        class normal;
        class texture;
        class group;
        class material;
    }

    class mtl_scanner;
    class mtl_parser;

    typedef std::vector<obj::face> face_set;
    typedef std::vector<obj::vertex> vertex_set;
    typedef std::vector<obj::normal> normal_set;
    typedef std::vector<obj::texture> texture_set;
    typedef std::vector<obj::group> texture_set;
    typedef std::map<std::string, obj::material> material_set;

    class obj_reader
    {
    public:
        obj_reader(const std::string &filename, bool trace_scanning, bool trace_parsing);
        ~obj_reader();

    public:
        bool read();
        
    private:
        void error(const obj_parser::location_type &loc, const std::string &msg);
        int yylex(obj_parser::semantic_type *lval, obj_parser::location_type *loc);
        
        bool _trace_scanning;
        bool _trace_parsing;
        std::string _filename;

        obj_parser _parser;
        obj_scanner _scanner;
        mtl_scanner _mtl_scanner;
        mtl_parser _mtl_parser;

        friend class obj_parser;
    };
}
