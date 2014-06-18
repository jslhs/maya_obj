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

	struct vertex
	{
		int size;
		union
		{
			vec3 pos3;
			vec4 pos4;
		};
	};

	struct texture
	{
		int size;
		union
		{
			float u;
			vec2 tex2;
			vec3 tex3;
		};
	};

	typedef vec3 normal;

	class face
		: public std::vector<indexed_vertex>
	{
	};


}
