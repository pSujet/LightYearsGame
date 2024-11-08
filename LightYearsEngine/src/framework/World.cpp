#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
	World::World(Application* owningApp)
		: mOningApp{ owningApp },
		mBeganPlay{ false },
		mActors{},
		mPendingActor{}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!mBeganPlay) {
			mBeganPlay = true;
			BeginPlay();
		}
			
	}
	void World::TickInternal(float deltaTime)
	{	
		for (shared<Actor> actor : mPendingActor)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}
		mPendingActor.clear();

		for(auto iter = mActors.begin(); iter != mActors.end();)
		{	
			// (*iter)->IsPendingDestroy()
			// -> We get shared<Actor>
			// get() We get raw *Actor
			// -> + get() = *
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
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
		for (auto actor : mActors)
		{
			actor->Render(window);
		}
	}
}