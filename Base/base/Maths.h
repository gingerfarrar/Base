#pragma once


#include "math\mathdef.h"

#include "math\flops.h"
#include "math\vec2.h"
#include "math\vec3.h"
#include "math\mat3.h"
#include "math\aabb.h"
#include "math\hull.h"
#include "math\collision.h"
#include "math\rand.h"

#include <random>
#include <cmath>

#define DEG2RAD 0.0174533




// TODO: add color struct from old lib
union color
{
	unsigned ui_color;
	struct { unsigned char a, b, r, g; };
};
// 0x00 00 00 00

inline color lerp(const color &S, const color &E, float t)
{
	color ret;
	ret.r = S.r*(1 - t) + E.r*t;
	ret.g = S.g*(1 - t) + E.g*t;
	ret.b = S.b*(1 - t) + E.b*t;
	ret.a = S.a*(1 - t) + E.a*t;
	return ret;
}

inline float lerp(float s, float e, float t)
{
	return s*(1 - t) + e*t;
}

inline base::vec2 randDir(float min_deg, float max_deg)
{
	float deg = lerp(min_deg, max_deg, base::rand01());
	float rad = DEG2RAD * deg;

	return base::vec2{ cos(rad), sin(rad) };
}