#include "framework/Application.h"
#include <iostream>
#include "framework/Core.h"
#include "framework/World.h" // Forward declaration in header but need to be included in cpp file

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style },
		mTargetFramerate{ 60.0f },
		mTickClock{},
		mCurrentWorld{nullptr}
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


			float frameDeltaTime = mTickClock.restart().asSeconds();
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

		if (mCurrentWorld) {			
			mCurrentWorld->TickInternal(deltaTime);
		}			
	}

	// Better practice to make in this template pattern with virtual functions
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{

	}

}
