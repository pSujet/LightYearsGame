#include "framework/Application.h"
#include <iostream>

namespace ly
{
	Application::Application()
		: mWindow{ sf::VideoMode(512, 720), "Light Years" },
		mTargetFramerate{ 60.0f },
		mTickClock{}
	{
		
	}
	void Application::Run() 
	{	
		mTickClock.restart();
		float accumulatedTime = 0.0f;
		float targetDeltaTime = 1.0f / mTargetFramerate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					mWindow.close();
			}


			float FrameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += FrameDeltaTime;
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
	}

	// better practice to make in this template pattern with virtual functions
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		sf::RectangleShape rect(sf::Vector2f(100.0f, 100.0f));
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
		mWindow.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{

	}

}
