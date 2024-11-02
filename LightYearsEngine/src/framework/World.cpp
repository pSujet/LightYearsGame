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

		for (shared<Actor> actor : _actors)
		{
			actor->Tick(deltaTime);
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
}