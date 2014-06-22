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
	typedef std::map<std::string, face_set> mtl_face_map;
	typedef std::map<std::string, face_set> obj_face_map;	

    class obj_reader
    {
    public:
        obj_reader(const std::string &filename, bool trace_scanning = false, bool trace_parsing = false);
        ~obj_reader();

    public:
        bool read();
        inline obj_scanner &scanner();
        inline obj_parser &parser();

        inline const vertex_set &vertices() const;
        inline const texture_set &textures() const;
        inline const normal_set &normals() const;
        inline const object_set &objects() const;
        inline const material_set &materials() const;
        inline const face_set &faces() const;
		inline const mtl_face_map &mtl_faces() const;
		inline const obj_face_map &obj_faces() const;	

    private:
		void parse_mtl(const std::string &filename);
        inline void error(const obj_parser::location_type &loc, const std::string &msg);
        
        inline void add(obj::object *obj);
        inline void add(obj::material *mtl);
        inline void add(obj::vertex *v);
        inline void add(obj::texture *t);
        inline void add(obj::normal *n);
        inline void add(obj::face *f);
		inline void set_mtl_name(std::string *name);
		
		inline void set_mtl_illum(int i)	  { if(_mtl) _mtl->illum = i; }
		inline void set_mtl_Tf(obj::vec3 *tf) { if(_mtl) _mtl->trans_filter = tf; }
		inline void set_mtl_Ka(obj::vec3 *ka) { if(_mtl) _mtl->ambient = ka; }
		inline void set_mtl_Kd(obj::vec3 *kd) { if(_mtl) _mtl->diffuse = kd; }
		inline void set_mtl_Ks(obj::vec3 *ks) { if(_mtl) _mtl->specular = ks; }
		inline void set_mtl_Ke(obj::vec3 *ke) { if(_mtl) _mtl->env = ke; }
		inline void set_mtl_Ns(float ns) { if(_mtl) _mtl->specular_n = ns; }
		inline void set_mtl_Ni(float ni) { if(_mtl) _mtl->optical_density = ni; }
		inline void set_mtl_d(float d)	 { if(_mtl) _mtl->dissolve = d; }
		inline void set_mtl_map_Ka(obj::tex_map *tex) { if(_mtl) _mtl->map_Ka = tex; }
		inline void set_mtl_map_Ks(obj::tex_map *tex) { if(_mtl) _mtl->map_Ks = tex; }
		inline void set_mtl_map_Kd(obj::tex_map *tex) { if(_mtl) _mtl->map_Kd = tex; }
		inline void set_mtl_map_Ns(obj::tex_map *tex) { if(_mtl) _mtl->map_Ns = tex; }
		inline void set_mtl_map_d(obj::tex_map *tex)  { if(_mtl) _mtl->map_d = tex; }
		inline void set_mtl_refl(obj::tex_map *tex)   { if(_mtl) _mtl->map_refl = tex; }
		inline void set_mtl_map_bump(obj::tex_map *tex)   { if(_mtl) _mtl->map_bump = tex; }
		inline void set_mtl_decal(obj::tex_map *tex)  { if(_mtl) _mtl->map_decal = tex; }
		inline void set_mtl_disp(obj::tex_map *tex)   { if(_mtl) _mtl->map_disp = tex; }

        inline obj::object *cur_obj() const;
        inline obj::material *cur_mtl() const;

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
		mtl_face_map _mtl_face_map;
		obj_face_map _obj_face_map;

        obj::object *_obj;
        obj::material *_mtl;

		std::string _mtl_name;
		std::string _obj_name;
		
		std::ifstream _fs;

		std::vector<obj::vec3 *> _vvals;
		std::vector<obj::tex_map *> _tvals;
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

	inline const mtl_face_map &obj_reader::mtl_faces() const
	{
		return _mtl_face_map;
	}

	inline const obj_face_map &obj_reader::obj_faces() const
	{
		return _obj_face_map;
	}

	inline void obj_reader::set_mtl_name(std::string *name)
	{
		if(name) _mtl_name = *name;
	}

    inline void obj_reader::add(obj::object *obj)
    {
        _obj = obj;
		if(_obj && _obj->name) _obj_name = *_obj->name;
		//_obj->mtl = _mtl_name;
        _objs.push_back(obj);
    }

    inline void obj_reader::add(obj::material *mtl)
    {
        _mtl = mtl;
        if(mtl && mtl->name) _mtls[*(mtl->name)] = mtl;
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
		_mtl_face_map[_mtl_name].push_back(f);
        _obj_face_map[_obj_name].push_back(f);
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

	inline const material_set &obj_reader::materials() const
	{
		return _mtls;
	}
}
