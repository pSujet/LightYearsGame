#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        :_owningWorld{owningWorld},
        _hasBeganPlay{false},
        _sprite{},
        _texture{}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor is destroyed !!!");
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

    void Actor::TickInternal(float deltaTime)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor ticking");
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        _texture.loadFromFile(texturePath);
        _sprite.setTexture(_texture);

        // Texture rectangle top left to bottom right
        int textureWidth = _texture.getSize().x;
        int textureHeight = _texture.getSize().y;
        _sprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}});
    }

    void Actor::Render(sf::RenderWindow& window)
    {   
        if (IsPendingDestroy())
            return;

        window.draw(_sprite);
    }
    
}

