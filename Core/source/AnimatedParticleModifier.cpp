#include "AnimatedParticleModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"

namespace bc
{
    AnimatedParticleModifier::AnimatedParticleModifier(se::Vector2 velocity, se::Vector2 size, se::AnimatedSprite sprite)
        : velocity(velocity)
        , startLifeTime(lifeTime)
        , size(size)
        , sprite(sprite)
    {

    }


    AnimatedParticleModifier::~AnimatedParticleModifier()
    {

    }


    void AnimatedParticleModifier::onCreate()
    {
        this->entity->getSprite().setScale(this->size);
    }


    void AnimatedParticleModifier::onUpdate(float elapsedTime)
    {
        this->sprite.move(this->velocity * elapsedTime * this->lifeTime / this->startLifeTime);

        this->sprite.update(elapsedTime);
        if (this->sprite.finishedAnimation())
            this->entity->dead = true;

        this->entity->getSprite().setPosition(this->sprite.getPosition());
    }


    void AnimatedParticleModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}