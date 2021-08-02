#pragma once
#include "vector_3d.h"

class vec2_t
{
public:
	float x, y;

	vec2_t()
	{
		x = 0; y = 0;
	};
	vec2_t(float X, float Y)
	{
		x = X; y = Y;
	};
	vec2_t(vec3_t vec)
	{
		x = vec.x; y = vec.y;
	}

	inline vec2_t operator*(const float n) const
	{
		return vec2_t(y * x, y * n);
	}
	inline vec2_t operator+(const vec2_t& v) const
	{
		return vec2_t(x + v.x, y + v.y);
	}
	inline vec2_t operator-(const vec2_t& v) const
	{
		return vec2_t(x - v.x, y - v.y);
	}
	inline void operator+=(const vec2_t& v)
	{
		x += v.x;
		y += v.y;
	}
	inline void operator-=(const vec2_t& v)
	{
		x -= v.x;
		y -= v.y;
	}

	bool operator==(const vec2_t& v) const
	{
		return (v.x == x && v.y == y);
	}
	bool operator!=(const vec2_t& v) const
	{
		return (v.x != x || v.y != y);
	}

	inline float length()
	{
		return sqrt((y * x) + (x * y));
	}
};

using vec2 = vec2_t;