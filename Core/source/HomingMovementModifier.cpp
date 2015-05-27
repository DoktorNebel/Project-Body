#include "HomingMovementModifier.h"

#include "MathFunctions.h"
#include "Entity.h"

namespace bc
{
    HomingMovementModifier::HomingMovementModifier(Entity* targetEntity, float speed, bool delayed)
        : targetEntity(targetEntity)
        , speed(speed)
        , delayed(delayed)
    {

    }


    HomingMovementModifier::~HomingMovementModifier()
    {

    }


    void HomingMovementModifier::onCreate()
    {
        this->targetPoint = this->targetEntity->getSprite().getPosition();
    }


    void HomingMovementModifier::onUpdate(float elapsedTime)
    {
        se::Vector2 direction;
        if (this->delayed)
        {
            direction = se::Math::GetNormalized(this->targetPoint - this->entity->getSprite().getPosition());
            if (se::Math::Distance(this->targetPoint, this->entity->getSprite().getPosition()) <= 2.0f)
            {
                this->targetPoint = this->targetEntity->getSprite().getPosition();
            }
        }
        else
        {
            direction = se::Math::GetNormalized(this->targetEntity->getSprite().getPosition() - this->entity->getSprite().getPosition());
        }
        this->entity->getSprite().setRotation(atan2(direction.y, direction.x) * 57.2957795f - 90.0f);
        this->entity->getSprite().move(direction * this->speed * elapsedTime);
    }


    void HomingMovementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}