#include "HomingMovementModifier.h"

#include "MathFunctions.h"
#include "Entity.h"

namespace bc
{
    HomingMovementModifier::HomingMovementModifier(Entity* targetEntity, float speed)
        : targetEntity(targetEntity)
        , speed(speed)
    {

    }


    HomingMovementModifier::~HomingMovementModifier()
    {

    }


    void HomingMovementModifier::onCreate()
    {

    }


    void HomingMovementModifier::onUpdate(float elapsedTime)
    {
        se::Vector2 direction = se::Math::GetNormalized(this->targetEntity->getSprite().getPosition() - this->entity->getSprite().getPosition());
        this->entity->getSprite().move(direction * this->speed * elapsedTime);
    }


    void HomingMovementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {

    }
}