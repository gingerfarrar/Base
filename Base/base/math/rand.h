#pragma once

#include <random>
#include "flops.h"
#include "vec2.h"

namespace base
{
inline float rand01() { return (float)rand() / RAND_MAX; }

inline float randRange(float a, float b) { return flops::lerp(a, b, rand01()); }

inline vec2 randRange(const vec2 &a, const vec2 &b)
{
	vec2 ret;
	ret.x = randRange(a.x,b.x);
	ret.y = randRange(a.y,b.y);
	return ret;
}
}