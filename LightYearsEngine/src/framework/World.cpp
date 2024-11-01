#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owningApp)
		: _owningApp{ owningApp },
		_beganPlay{ false }
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
		Tick(deltaTime);
	}
	World::~World()
	{
	}
	void World::BeginPlay()
	{
		LOG("began play");
	}
	void World::Tick(float deltaTime)
	{
		LOG("tick %f", 1.f/deltaTime);
	}
}