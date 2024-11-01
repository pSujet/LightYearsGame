#include "framework/Application.h"
#include <iostream>
#include <framework/Core.h>
#include <framework/World.h> // Forward declaration in header but need to be included in cpp file

namespace ly
{
	Application::Application()
		: _Window{ sf::VideoMode(512, 720), "Light Years" },
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
		while (_Window.isOpen())
		{
			sf::Event windowEvent;
			while (_Window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					_Window.close();
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
		_Window.clear();

		Render();

		_Window.display();
	}

	void Application::Render()
	{
		sf::RectangleShape rect(sf::Vector2f(100.0f, 100.0f));
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
		rect.setPosition(_Window.getSize().x / 2.f, _Window.getSize().y / 2.f);
		_Window.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{

	}

}
