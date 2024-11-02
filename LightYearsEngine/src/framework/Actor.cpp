#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld)
        :_owningWorld(owningWorld),
        _hasBeganPlay(false)
    {

    }
    Actor::~Actor()
    {
        
    }
    void Actor::BeginPlayInternal()
    {
         if(!_hasBeganPlay)
         {
            _hasBeganPlay = true;
            BeginPlay();
         }
    }
    void Actor::BeginPlay()
    {
        LOG("Actor begin play!");
    }
    void Actor::Tick(float deltaTime)
    {
        LOG("Actor ticking");
    }
}
