#include "HomingMovementModifier.h"

#include <algorithm>
#include "MathFunctions.h"
#include "Entity.h"

namespace bc
{
    HomingMovementModifier::HomingMovementModifier(Entity* targetEntity, float speed, bool delayed, float maxTurnRate)
        : targetEntity(targetEntity)
        , targetEntities(0)
        , speed(speed)
        , delayed(delayed)
        , maxTurnRate(maxTurnRate)
    {

    }


    HomingMovementModifier::HomingMovementModifier(std::vector<Entity>* targetEntities, float speed, bool delayed, float maxTurnRate)
        : targetEntity(0)
        , targetEntities(targetEntities)
        , speed(speed)
        , delayed(delayed)
        , maxTurnRate(maxTurnRate)
    {

    }


    HomingMovementModifier::~HomingMovementModifier()
    {

    }


    void HomingMovementModifier::onCreate()
    {
        if (this->targetEntities)
        {
            std::vector<Entity>::iterator iter = std::min_element(this->targetEntities->begin(), this->targetEntities->end(), [this](Entity& left, Entity& right)
            {
                return se::Math::Distance(left.getSprite().getPosition(), this->entity->getSprite().getPosition()) < se::Math::Distance(right.getSprite().getPosition(), this->entity->getSprite().getPosition());
            });
            this->targetEntity = &*iter;
        }
        this->targetPoint = this->targetEntity->getSprite().getPosition();
    }


    void HomingMovementModifier::onUpdate(float elapsedTime)
    {
        se::Vector2 targetDirection;
        if (this->delayed)
        {
            targetDirection = se::Math::GetNormalized(this->targetPoint - this->entity->getSprite().getPosition());
            if (se::Math::Distance(this->targetPoint, this->entity->getSprite().getPosition()) <= 2.0f)
            {
                this->targetPoint = this->targetEntity->getSprite().getPosition();
            }
        }
        else
        {
            targetDirection = se::Math::GetNormalized(this->targetEntity->getSprite().getPosition() - this->entity->getSprite().getPosition());
        }
        this->direction = se::Math::Lerp(this->direction, targetDirection, this->maxTurnRate);
        this->entity->getSprite().setRotation(atan2(this->direction.y, this->direction.x) * 57.2957795f - 90.0f);
        this->entity->getSprite().move(this->direction * this->speed * elapsedTime);
    }


    void HomingMovementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}