#pragma once

#include <vector>

namespace obj
{
	struct indexed_vertex
	{
		int pos;
		int tex;
		int norm;
	};

	template<class T>
	struct vec2_t
	{
		union
		{
			struct { T x, y; }
			struct { T u, v; }
			struct { T s, t; }
		};
	};

	template<class T>
	struct vec3_t
	{
		union
		{
			struct { T x, y, z; }
			struct { T r, g, b; }
			struct { T u, v, w; }
			struct { T i, j, k; }
		};
	};

	template<class T>
	struct vec4_t
	{
		union
		{
			struct { T x, y, z, w; }
			struct { T r, g, b, a; }
		};
	};

	typedef vec2_t<float> vec2;
	typedef vec3_t<float> vec3;
	typedef vec4_t<float> vec4;
    
    typedef vec4 vertex;
    typedef vec3 texture;
	typedef vec3 normal;
    typedef std::vector<indexed_vertex> face;
    
    struct material
    {
        std::string name;
        float ambient;
        float sharpness;
        float diffusion;
        std::string map_Kd;
        std::string map_Ks;
    };

    typedef std::vector<face> face_set;
    typedef std::map<std::string, material> material_set;
    
    class object
    {
    public:
        object(const std::string &name, material *mtl = nullptr);
        ~object();

        const std::string &name() const;
        material *mtl() const;
        const std::string &faces() const;

    private:
        std::string _name;
        material *_mtl;
        face_set _faces;
    };
}
