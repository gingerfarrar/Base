#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"
#include "constdecl.h"


class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship, spr_bullet, spr_roid, spr_font, puff_sprite;
	ObjectPool<Entity>::iterator currentCamera;

public:
	virtual void init()
	{
		spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_ship = sfw::loadTextureMap("../res/ship.png");
		spr_roid = sfw::loadTextureMap("../res/rock.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
		puff_sprite = sfw::loadTextureMap("../res/particle_sprite.png");
	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->camera->offset = vec2{ 400,300 };
		//currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });
		
		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);

		factory.spawnPlayer(spr_ship, spr_font, puff_sprite);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);

		//for (int i = 0; i < 200; ++i)
		{
			factory.spawnImage(puff_sprite, 0, -20, 50, 50);
		}
	}

	virtual void stop()
	{

	}

	
	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference


			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// controller update
			if (e.transform && e.rigidbody && e.controller)
			{
				vec2 stuff = currentCamera->transform->getGlobalPosition();
				stuff = e.transform->getGlobalPosition();
				currentCamera->transform->setGlobalPosition(stuff);
				e.controller->poll(&e.transform, &e.rigidbody, dt);
				if (e.controller->shotRequest) // controller requested a bullet fire
				{
					factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition()  + e.transform->getGlobalUp()*48,
											vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
				}
			}
			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
			// particle system
			if (e.part && e.transform && e.sprite)
			{
				e.part->update(&e.transform, dt);
			}
		}

		// Physics system!
		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{
							// condition for dynamic resolution
							if (it->rigidbody && bit->rigidbody)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)							
									base::StaticResolution(cd, &it->transform, &it->rigidbody);					
						}
					}
				}
	}


	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);
	
		for each(auto &e in factory)
			if (e.transform && e.part)
				e.part->draw(cam);


		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);

#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);
#endif
	}

	virtual size_t next() const 
	{
		return GAAMESTATE;
	}
};

