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
    
    struct material
    {
        std::string name;
        float ambient;
        float sharpness;
        float diffusion;
        std::string map_Kd;
        std::string map_Ks;

		material() { }
		material(const std::string &n) : name(n) { }
    };

    struct object
    {
        std::string name;
        std::vector<face *> faces;
        material *mtl;

		object() : mtl(nullptr) { }
		object(const std::string &n, material *m = nullptr)
			: name(n)
			, mtl(m)
		{
		}
    };

}
