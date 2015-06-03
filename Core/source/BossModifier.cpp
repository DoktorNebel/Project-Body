#include "BossModifier.h"

#include "Entity.h"

namespace bc
{
    void BossModifier::onCreate()
    {

    }


    void BossModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->health <= 0.0f)
            this->entity->dead = true;
    }


    void BossModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}