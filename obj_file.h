#pragma once

#include <string>
#include <vector>

namespace obj
{
	struct ivertex
	{
		int pos;
		int tex;
		int norm;

		ivertex()
			: pos(0)
			, tex(0)
			, norm(0)
		{
		}

		ivertex(int p, int n)
			: pos(p)
			, tex(0)
			, norm(n)
		{
		}

		ivertex(int p, int t, int n)
			: pos(p)
			, tex(t)
			, norm(n)
		{
		}
	};

	template<class T>
	struct vec2_t
	{
		union
		{
			struct { T x, y; };
			struct { T u, v; };
			struct { T s, t; };
			T d[2];
		};

		vec2_t()
			: x(0)
			, y(0)
		{
		}

		vec2_t(T v1, T v2)
			: x(v1)
			, y(v2)
		{
		}
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
			T d[3];
		};

		vec3_t()
			: x(0)
			, y(0)
			, z(0)
		{
		}

		vec3_t(T v1, T v2, T v3)
			: x(v1)
			, y(v2)
			, z(v3)
		{
		}
	};

	template<class T>
	struct vec4_t
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			T d[4];
		};

		vec4_t()
			: x(0)
			, y(0)
			, z(0)
			, w(0)
		{
		}

		vec4_t(T v1, T v2, T v3, T v4)
			: x(v1)
			, y(v2)
			, z(v3)
			, w(v4)
		{
		}
	};

	typedef vec2_t<float> vec2;
	typedef vec3_t<float> vec3;
	typedef vec4_t<float> vec4;
    
    struct vertex : vec4
	{
		vertex() { }
		vertex(float x, float y, float z, float w = 0) : vec4(x, y, z, w) { }
	};

    struct texture : vec3
	{
		texture() { }
		texture(float u, float v = 0, float w = 0) : vec3(u, v, w) { }
	};

    struct normal : vec3
	{
		normal() { }
		normal(float i, float j, float k) : vec3(i, j, k) { }
	};

	class face
		: public std::vector<ivertex *>
	{
	public:
		face() { }
		face(ivertex *v1, ivertex *v2, ivertex *v3)
		{
			push_back(v1);
			push_back(v2);
			push_back(v3);
		}

		face(ivertex *v1, ivertex *v2, ivertex *v3, ivertex *v4)
		{
			push_back(v1);
			push_back(v2);
			push_back(v3);
			push_back(v4);
		}
	};

	struct tex_map
	{
		std::string *file;
		vec3 *org;
		vec3 *scale;
		vec3 *tur;
		bool blendu;
		bool blendv;
		float boost;
		bool clamp;

        tex_map(std::string *fn = nullptr)
            : file(fn)
            , org(nullptr)
            , scale(nullptr)
            , tur(nullptr)
            , blendu(false)
            , blendv(false)
            , boost(false)
            , clamp(false) 
        {
        }
	};
    
    struct material
    {
        std::string *name;
        vec3 *ambient;
        vec3 *diffuse;
        vec3 *specular;
		vec3 *env;
		vec3 *trans_filter;
		
		int illum;
        float specular_n;
		float dissolve;
		float optical_density;
		
		tex_map *map_Ka;			// ambient texture map
		tex_map *map_Kd;			// diffuse texture map
        tex_map *map_Ks;			// specular color texture map
		tex_map *map_Ns;			// specular highlight component
		tex_map *map_opacity;		// 
		tex_map *map_d;				// alpha texture map
		tex_map *map_bump;			// bump map
		tex_map *map_refl;			// reflection map
		tex_map *map_decal;
		tex_map *map_disp;

		material(std::string *n = nullptr) 
			: name(n)
			, ambient(nullptr)
			, diffuse(nullptr)
			, specular(nullptr)
			, env(nullptr)
			, trans_filter(nullptr)
			, illum(0)
			, specular_n(0)
			, dissolve(1.0)
			, optical_density(0)
			, map_Ka(nullptr)
			, map_Kd(nullptr)
			, map_Ks(nullptr)
			, map_Ns(nullptr)
			, map_opacity(nullptr)
			, map_d(nullptr)
			, map_bump(nullptr)
			, map_refl(nullptr)
		{ 
		}

    };

    struct object
    {
        std::string *name;

		object() { }
		object(std::string *n = nullptr)
			: name(n)
		{
		}
    };

}
