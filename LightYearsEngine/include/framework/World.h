#pragma once

namespace ly 
{
	class Application; // Forward declaration
	class World
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual ~World();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* _owningApp;
		bool _beganPlay;

	};
}