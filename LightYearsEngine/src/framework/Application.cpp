#include "framework/Application.h"
#include <iostream>
#include "framework/Core.h"
#include "framework/World.h" // Forward declaration in header but need to be included in cpp file

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: _window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		_TargetFramerate{ 60.0f },
		_TickClock{},
		currentWorld{nullptr}
	{
		
	}
	void Application::Run() 
	{	
		_TickClock.restart();
		float accumulatedTime = 0.0f;
		float targetDeltaTime = 1.0f / _TargetFramerate;
		while (_window.isOpen())
		{
			sf::Event windowEvent;
			while (_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					_window.close();
			}


			float frameDeltaTime = _TickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			//update the frame at the targetDeltaTime
			while (accumulatedTime >= targetDeltaTime)
			{
				//subtract the targetDeltaTime from accumulatedTime to ensure that we don't miss any ticks even in a slow machine
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld) {			
			currentWorld->TickInternal(deltaTime);
		}			
	}

	// Better practice to make in this template pattern with virtual functions
	void Application::RenderInternal()
	{
		_window.clear();

		Render();

		_window.display();
	}

	void Application::Render()
	{
		if (currentWorld)
		{
			currentWorld->Render(_window);
		}
	}

	void Application::Tick(float deltaTime)
	{

	}

}
