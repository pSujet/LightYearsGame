#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
	World::World(Application* owningApp)
		: _owningApp{ owningApp },
		_beganPlay{ false },
		_actors{},
		_pendingActor{}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!_beganPlay) {
			_beganPlay = true;
			BeginPlay();
		}
			
	}
	void World::TickInternal(float deltaTime)
	{	
		for (shared<Actor> actor : _pendingActor)
		{
			_actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		_pendingActor.clear();

		for(auto iter = _actors.begin(); iter != _actors.end();)
		{	
			// (*iter)->IsPendingDestroy()
			// -> We get shared<Actor>
			// get() We get raw *Actor
			// -> + get() = *
			if (iter->get()->IsPendingDestroy())
			{
				iter = _actors.erase(iter);
			}
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}


		Tick(deltaTime);
	}
	World::~World()
	{
	}
	void World::BeginPlay()
	{
		LOG("===== Begin play =====");
	}
	void World::Tick(float deltaTime)
	{
		LOG("tick %f", 1.f/deltaTime);
	}
	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : _actors)
		{
			actor->Render(window);
		}
	}
}