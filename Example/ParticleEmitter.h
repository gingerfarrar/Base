#pragma once
#include "particle.h"
#include "base\data\ObjectPool.h"
#include "base\math\vec2.h"
#include "base\Maths.h"
#include "base\math\rand.h"

#include "base\components\Transform.h"

#define PART_SIZE 10000

class ParticleEmitter
{
	// Data Structure to store all of our particles
	particle particles[PART_SIZE];
	//base::ObjectPool<particle> particles;

	particle emit(vec2 pos, float ang)
	{
		for(int i = 0; i < PART_SIZE; ++i) // linear time every time we add a particle
			if (!particles[i].isActive())
			{
				return particles[i] = _generate(pos, ang);				
			}
		//particles.push(_generate());
	}

	particle _generate(vec2 a_pos, float a_ang)
	{
		particle part;
		part.pos = (mat3::rotate(a_ang) * base::vec3(pos,1)).xy + a_pos;
		part.sprite = sprite;
		
		
		vec2 dir = randDir(angLo, angHi);

		dir = (mat3::rotate(a_ang)  * base::vec3(dir, 0)).xy;

		part.vel = (dir) * lerp(spdLo, spdHi, base::rand01());

		part.lifespan = lerp(lifespanLo, lifespanHi, base::rand01());

		part.sColor = lerp(colLoStart, colHiStart, base::rand01());
		part.eColor = lerp(colLoEnd, colHiEnd, base::rand01());

		part.sDim = randRange(dimLoStart, dimHiStart);
		part.eDim = randRange(dimLoEnd, dimHiEnd);

		part.lifetime = 0;
		return part;
	}

	float emissionTimer;

public:
	float emitRateLo, emitRateHi;

	ParticleEmitter() : emissionTimer(0) { }

	vec2 pos;
	unsigned sprite;
	float angLo, angHi; // direction *
	float spdLo, spdHi; // speed = velocity
	vec2  dimLoStart, dimHiStart; // range of acceptable starting dimensions
	vec2  dimLoEnd, dimHiEnd;	  // range of acceptable ending dimensions
	color colLoStart, colHiStart; // ....
	color colLoEnd, colHiEnd;
	float lifespanLo, lifespanHi;


	void update(const base::Transform *T, float dt)
	{
		
		for (int i = 0; i < PART_SIZE; ++i)
		{
			if(particles[i].isActive())
				particles[i].refresh(dt);
		}

		emissionTimer -= dt;
		while (emissionTimer < 0)
		{
			particle &p = emit(T->getGlobalPosition(), T->getGlobalAngle());

			emissionTimer += lerp(emitRateLo, emitRateHi, base::rand01());
		}
	}


	void draw(const mat3 &cam) const
	{
		mat3 glob = cam;

		//mat3 glob = cam * T->getGlobalTransform();
		for (int i = 0; i < PART_SIZE; ++i)
		{
			if (particles[i].isActive())
			{
				particles[i].draw(glob);
			}
		}
	}
};