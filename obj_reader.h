#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "obj_file.h"
#include "obj_scanner.h"
#include "obj_parser.h"

namespace utility
{
    typedef std::vector<obj::vertex *> vertex_set;
    typedef std::vector<obj::texture *> texture_set;
    typedef std::vector<obj::normal *> normal_set;
    typedef std::vector<obj::face *> face_set;
    typedef std::map<std::string, obj::material *> material_set;
    typedef std::vector<obj::object *> object_set; 

    class obj_reader
    {
    public:
        obj_reader(const std::string &filename, bool trace_scanning = false, bool trace_parsing = false);
        ~obj_reader();

    public:
        bool read();
        obj_scanner &scanner();
        obj_parser &parser();

        const vertex_set &vertices() const;
        const texture_set &textures() const;
        const normal_set &normals() const;
        const object_set &objects() const;
        const material_set &materials() const;
        const face_set &faces() const;        

    private:
		void parse_mtl(const std::string &filename);
        void error(const obj_parser::location_type &loc, const std::string &msg);
        
        void add(obj::object *obj);
        void add(obj::material *mtl);
        void add(obj::vertex *v);
        void add(obj::texture *t);
        void add(obj::normal *n);
        void add(obj::face *f);

        obj::object *cur_obj() const;
        obj::material *cur_mtl() const;

        friend class obj_parser;

    private:
        bool _trace_scanning;
        bool _trace_parsing;
        bool _error;
		std::string _obj_filename;
		std::string _mtl_filename;

		std::ifstream _obj_fs;
		std::ifstream _mtl_fs;

        obj_parser _parser;
        obj_scanner _scanner;

        object_set _objs;
        material_set _mtls;
        vertex_set _verts;
        texture_set _texs;
        normal_set _norms;
        face_set _faces;

        obj::object *_obj;
        obj::material *_mtl;

		std::ifstream _fs;
    };

    inline void obj_reader::error(const obj_parser::location_type &loc, const std::string &msg)
    {
        _error = true;
        std::cerr << loc << ":" << msg << std::endl;
    }

    inline obj_scanner &obj_reader::scanner()
    {
        return _scanner;
    }

    inline obj_parser &obj_reader::parser()
    {
        return _parser;
    }

    inline void obj_reader::add(obj::object *obj)
    {
        _obj = obj;
        _objs.push_back(obj);
    }

    inline void obj_reader::add(obj::material *mtl)
    {
        _mtl = mtl;
        _mtls[mtl->name] = mtl;
    }

    inline void obj_reader::add(obj::vertex *v)
    {
        _verts.push_back(v);
    }

    inline void obj_reader::add(obj::texture *t)
    {
        _texs.push_back(t);
    }

    inline void obj_reader::add(obj::normal *n)
    {
        _norms.push_back(n);
    }

    inline void obj_reader::add(obj::face *f)
    {
        _faces.push_back(f);
        if(_obj) _obj->faces.push_back(f);
    }

    inline obj::object *obj_reader::cur_obj() const
    {
        return _obj;
    }

    inline obj::material *obj_reader::cur_mtl() const
    {
        return _mtl;
    }

    inline const object_set &obj_reader::objects() const
    {
        return _objs;
    }

    inline const vertex_set &obj_reader::vertices() const
    {
        return _verts;
    }

    inline const texture_set &obj_reader::textures() const
    {
        return _texs;
    }

    inline const normal_set &obj_reader::normals() const
    {
        return _norms;
    }

    inline const face_set &obj_reader::faces() const
    {
        return _faces;
    }
}
