#include "ShakyMovementModifier.h"

#include "Entity.h"
#include "MathFunctions.h"

namespace bc
{
    void ShakyMovementModifier::onCreate()
    {

    }


    void ShakyMovementModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(se::Vector2(rand() % 301 - 150, rand() % 126 - 175) * elapsedTime);
    }


    void ShakyMovementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}