#include "ProjectileModifier.h"

#include "Entity.h"
#include "MathFunctions.h"

namespace bc
{
    void ProjectileModifier::onCreate()
    {
        this->velocity = se::Vector2(0.0f, 1000.0f);
        this->lifeTime = 1.0f;
    }


    void ProjectileModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->velocity * elapsedTime);
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->health = 0.0f;
    }


    void ProjectileModifier::onHit(Entity* otherEntity)
    {

    }
}