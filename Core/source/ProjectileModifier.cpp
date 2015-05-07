#include "ProjectileModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"
#include "ParticleModifier.h"

namespace bc
{
    ProjectileModifier::ProjectileModifier(se::Vector2(velocity), float lifeTime)
        : velocity(velocity)
        , lifeTime(lifeTime)
    {

    }


    ProjectileModifier::~ProjectileModifier()
    {

    }


    void ProjectileModifier::onCreate()
    {
        this->entity->getSprite().setRotation(atan2(this->velocity.x, this->velocity.y) * -57.2957795f);
        this->entity->getSprite().setDepth(0.1f);
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
    }


    void ProjectileModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->velocity * elapsedTime);
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->dead = true;
    }


    void ProjectileModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        otherEntity->health -= 10.0f;
        this->entity->health = 0.0f;
    }
}