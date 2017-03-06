#pragma once

#include "Entity.h"
#include "base\data\ObjectPool.h"
#include "base\Components.h"
class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;
	ObjectPool<PlayerController> controllers;
	ObjectPool<ParticleEmitter>   particles;

public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	
	Factory(size_t size = 512)
								: entities(size), transforms(size), rigidbodies(size),
								  colliders(size), sprites(size), lifetimes(size),
								  cameras(size), controllers(size), texts(size), particles(size)
	{
	}

	
	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{w,h};
		e->transform->setLocalPosition(vec2{ x,y });	

		return e;
	}
	ObjectPool<Entity>::iterator spawnImage(unsigned sprite, float x, float y, float w, float h, float time = -1)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{ w,h };
		e->transform->setLocalPosition(vec2{ x,y });

		if (time > 0)
		{
			e->lifetime = lifetimes.push();
			e->lifetime->lifespan = time;
		}
		return e;
	}

	ObjectPool<Entity>::iterator spawnBullet(unsigned sprite, vec2 pos, vec2 dim, float ang, float impulse, unsigned faction)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->transform->setLocalAngle(ang);

		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{1.2f, 1.2f};

		e->rigidbody->addImpulse(e->transform->getGlobalUp() * impulse);

		e->lifetime->lifespan = 1.6f;
		
		return e;
	}

	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font, unsigned particle)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();
		e->text = texts.push();

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		e->text->setString("Player1");

		e->transform->setLocalScale(vec2{48,48});

		e->sprite->sprite_id = sprite;


		e->part = particles.push();

		e->part->sprite = particle;
		e->part->angHi = 230;
		e->part->angLo = 310;
		e->part->colHiEnd.ui_color = RED;
		e->part->colHiStart.ui_color = YELLOW;
		e->part->colLoEnd.ui_color = NONE;
		e->part->colLoStart.ui_color = RED;
		e->part->dimHiEnd = vec2{ 412,412 };
		e->part->dimHiStart = vec2{ 32,32 };
		e->part->dimLoEnd = vec2{ 100,100 };
		e->part->dimLoStart = vec2{ 8,8 };
		e->part->emitRateHi = 0.02f;
		e->part->emitRateLo = 0.01f;
		e->part->lifespanHi = 3.7f;
		e->part->lifespanLo = 1.5f;
		e->part->pos = vec2{ 0, -20 };
		e->part->spdHi = 200;
		e->part->spdLo = 100;



		return e;
	}


	ObjectPool<Entity>::iterator spawnAsteroid(unsigned sprite)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		

		e->transform->setLocalScale(vec2{ 48,48 });

		e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;

		
		return e;
	}
};


