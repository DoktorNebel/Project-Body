#include "EnemyModifier.h"

#include "Entity.h"
#include "Engine.h"

namespace bc
{
    void EnemyModifier::onCreate()
    {
        this->entity->health = 100.0f;
        this->entity->maxHealth = 100.0f;
    }


    void EnemyModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(se::Vector2(0.0f, -100.0f * elapsedTime));
        if (this->entity->getSprite().getPosition().y < -(int)se::Engine::getSettings().resolutionHeight / 2)
            this->entity->health = 0.0f;
    }


    void EnemyModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        otherEntity->health -= this->entity->maxHealth / 5.0f;
    }
}