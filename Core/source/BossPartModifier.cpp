#include "BossPartModifier.h"

#include "BossModifier.h"
#include "Entity.h"

namespace bc
{
    BossPartModifier::BossPartModifier(BossModifier* boss)
        : boss(boss)
    {

    }


    void BossPartModifier::onCreate()
    {

    }


    void BossPartModifier::onUpdate(float elapsedTime)
    {
        if (this->boss->entity->health <= 0)
        {
            this->entity->dead = true;
            this->boss = 0;
        }
    }


    void BossPartModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::PlayerProjectiles && this->boss != 0)
        {
            this->boss->entity->health -= otherEntity->damage;
            otherEntity->dead = true;
        }
    }
}