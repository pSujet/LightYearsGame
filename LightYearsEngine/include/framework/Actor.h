#pragma once

namespace ly 
{
    class World;
    class Actor
    {
    public:
        Actor(World* owningWorld);
        virtual ~Actor();
        void BeginPlayInternal();
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

    
    private:
        World* _owningWorld;
        bool _hasBeganPlay;
    };
}