#include "ParticleModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"

namespace bc
{
    ParticleModifier::ParticleModifier(se::Vector2 velocity, se::Vector2 size, float lifeTime)
        : velocity(velocity)
        , lifeTime(lifeTime)
        , startLifeTime(lifeTime)
        , size(size)
    {

    }


    ParticleModifier::~ParticleModifier()
    {

    }


    void ParticleModifier::onCreate()
    {
        this->entity->getSprite().setScale(this->size);
    }


    void ParticleModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->velocity * elapsedTime * this->lifeTime / this->startLifeTime);
        this->entity->getSprite().setScale(this->size * this->lifeTime / this->startLifeTime);
        this->entity->getSprite().setColor(se::Vector4(1.0f, 1.0f, 1.0f, this->lifeTime / this->startLifeTime));
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->dead = true;
    }


    void ParticleModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}