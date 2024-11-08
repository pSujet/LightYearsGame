#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Core.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly 
{
	GameApplication::GameApplication()
		:Application{600, 980, "LightYearsGame", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		mActorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		mActorToDestroy.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_green.png");
		counter = 0;
	}
	void GameApplication::Tick(float deltaTime)
	{	
		counter += deltaTime;
		LOG("Current time: %f", counter);
		if (counter > 2.f)
		{
			if (!mActorToDestroy.expired())
			{
				mActorToDestroy.lock()->Destroy();
			}
		}
	}

}

