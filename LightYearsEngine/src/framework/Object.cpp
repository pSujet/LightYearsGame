#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object()
        : _isPendingDestroy{false}
    {

    }
    Object::~Object()
    {
        LOG("Object is Destroyed");
    }
    void Object::Destroy()
    {
        _isPendingDestroy = true;
    }
}