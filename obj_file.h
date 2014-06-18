#pragma once

#include <string>
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
			struct { T x, y; };
			struct { T u, v; };
			struct { T s, t; };
		};
	};

	template<class T>
	struct vec3_t
	{
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T u, v, w; };
			struct { T i, j, k; };
		};
	};

	template<class T>
	struct vec4_t
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
	};

	typedef vec2_t<float> vec2;
	typedef vec3_t<float> vec3;
	typedef vec4_t<float> vec4;
    
    struct vertex : vec4{};
    struct texture : vec3{};
    struct normal : vec3{}; 
    typedef std::vector<indexed_vertex *> face;
    
    struct material
    {
        std::string name;
        float ambient;
        float sharpness;
        float diffusion;
        std::string map_Kd;
        std::string map_Ks;
    };

    struct object
    {
        std::string name;
        std::vector<face *> faces;
        material *mtl;
    };

}
