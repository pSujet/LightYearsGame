#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application();
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float deltaTime);
		sf::RenderWindow _Window;
		float _TargetFramerate;
		sf::Clock _TickClock;
		shared<World> currentWorld;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld() 
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}