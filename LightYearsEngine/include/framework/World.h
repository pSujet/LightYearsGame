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
		Application* _owningApp;
		bool _beganPlay;

		List<shared<Actor>> _actors;
		List<shared<Actor>> _pendingActor; //Avoiding wrong adding in the actors list between the tick
	};

	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this}};
		_pendingActor.push_back(newActor);
		return newActor; // Implicit conversion from shared to weak pointer
	}
}