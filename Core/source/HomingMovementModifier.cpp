#include "HomingMovementModifier.h"

#include <algorithm>
#include "MathFunctions.h"
#include "Entity.h"
#include "Spawner.h"

namespace bc
{
    HomingMovementModifier::HomingMovementModifier(std::vector<CollisionGroup::Type> targetGroups, float speed, bool delayed, float maxTurnRate, float startRotation)
        : targetEntity(0)
        , targetGroups(targetGroups)
        , speed(speed)
        , delayed(delayed)
        , maxTurnRate(maxTurnRate)
    {
        float radRot = startRotation * 0.0174532925f;
        this->direction = se::Vector2(cos(radRot), sin(radRot));
    }


    HomingMovementModifier::~HomingMovementModifier()
    {

    }


    void HomingMovementModifier::onCreate()
    {
        float minDistance = 100000.0f;
        for (unsigned int i = 0; i < this->targetGroups.size(); ++i)
        {
            std::vector<Entity>* entities = Spawner::getEntities(this->targetGroups[i]);
            std::vector<Entity>::iterator iter = std::min_element(entities->begin(), entities->end(), [this](Entity& left, Entity& right)
            {
                return se::Math::Distance(left.getSprite().getPosition(), this->entity->getSprite().getPosition()) < se::Math::Distance(right.getSprite().getPosition(), this->entity->getSprite().getPosition());
            });

            if (iter != entities->end())
            {
                float distance = se::Math::Distance(iter->getSprite().getPosition(), this->entity->getSprite().getPosition());
                if (distance < minDistance)
                {
                    this->targetEntity = &*iter;
                    minDistance = distance;
                }
            }
        }
            
        this->targetPoint = this->targetEntity ? this->targetEntity->getSprite().getPosition() : this->entity->getSprite().getPosition() + this->direction * 500.0f;
    }


    void HomingMovementModifier::onUpdate(float elapsedTime)
    {
        if ((this->targetEntity && this->targetEntity->health <= 0.0f) || this->entity->getSprite().getPosition().x < -1000.0f || this->entity->getSprite().getPosition().x > 1000.0f)
        {
            this->targetEntity = 0;
            this->entity->dead = true;
        }

        if (this->targetEntity)
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
                this->targetPoint = this->targetEntity->getSprite().getPosition();
            }
            this->direction = se::Math::Lerp(this->direction, targetDirection, se::Math::Clamp(0.0f, 1.0f, this->maxTurnRate * elapsedTime));

            if (this->maxTurnRate < 1.0f)
            {
                float distance = se::Math::Distance(this->targetPoint, this->entity->getSprite().getPosition());
                this->maxTurnRate = 5000.0f / distance;
                //this->maxTurnRate = this->maxTurnRate > 1.0f ? 1.0f : this->maxTurnRate;
            }
        }
        
        this->entity->getSprite().setRotation(atan2(this->direction.y, this->direction.x) * 57.2957795f - 90.0f);
        this->entity->getSprite().move(this->direction * this->speed * elapsedTime);

    }


    void HomingMovementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}