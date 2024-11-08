#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly 
{
	class Actor;
	class Application; // Forward declaration
	class World
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType>
		weak<ActorType> SpawnActor();
		

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* mOningApp;
		bool mBeganPlay;

		List<shared<Actor>> mActors;
		List<shared<Actor>> mPendingActor; //Avoiding wrong adding in the actors list between the tick
	};

	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this}};
		mPendingActor.push_back(newActor);
		return newActor; // Implicit conversion from shared to weak pointer
	}
}