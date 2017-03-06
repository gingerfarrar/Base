#pragma once
#include "sfwdraw.h"
#include "base\Maths.h"

using base::vec2;
using base::mat3;

struct particle
{
private:
	vec2 m_dim;
	color m_color;
public:
	unsigned sprite;
	vec2 pos, vel;
	vec2 sDim, eDim;
	color sColor, eColor;

	float lifetime, lifespan;

	particle() : lifespan(-1), lifetime(0) {}

	bool refresh(float dt)
	{
		lifetime += dt;

		float alpha = lifetime / lifespan;

		m_dim = lerp(sDim, eDim, alpha);
		m_color = lerp(sColor, eColor, alpha);

		pos = pos + vel * dt;

		//sfw::drawTexture(sprite, pos.x, pos.y, dim.x, dim.y, 0, true, 0, color.ui_color);

		return alpha < 1;
	}

	bool isActive() const { return lifetime < lifespan; }


	void draw(const mat3 &glob) const
	{
		// build a matrix for the dim, pos

		mat3 part = mat3::translate(pos) * mat3::scale(m_dim);

		sfw::drawTextureMatrix3(sprite, 0, m_color.ui_color, (glob*part).v, 0);
	}
};