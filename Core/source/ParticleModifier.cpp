#include "ParticleModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"

namespace bc
{
    ParticleModifier::ParticleModifier(se::Vector2(velocity), float lifeTime)
        : velocity(velocity)
        , lifeTime(lifeTime)
        , startLifeTime(lifeTime)
    {

    }


    ParticleModifier::~ParticleModifier()
    {

    }


    void ParticleModifier::onCreate()
    {

    }


    void ParticleModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->velocity * elapsedTime * this->lifeTime / this->startLifeTime);
        this->entity->getSprite().setScale(se::Vector2(2, 2) * this->lifeTime / this->startLifeTime);
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->dead = true;
    }


    void ParticleModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {

    }
}