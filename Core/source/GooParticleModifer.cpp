#include "GooParticleModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "GooModifier.h"

namespace bc
{
    GooParticleModifier::GooParticleModifier(GooModifier* modifier)
        : modifier(modifier)
        , prevMidPoint(modifier->getMidPoint())
        , minSize((rand() % 11 + 10) / 10.0f)
        , maxSize((rand() % 81 + 20) / 10.0f)
        , scaleSpeed((rand() % 100 + 1) / 50.0f)
        , rotationSpeed((rand() % 1001 - 500) / 50.0f)
    {

    }


    GooParticleModifier::~GooParticleModifier()
    {

    }


    void GooParticleModifier::onCreate()
    {
        this->entity->getSprite().setColor(se::Vector4(0.3f, 0.8f, 0.1f, 0.8f));
        float scale = se::Math::Lerp(this->minSize, this->maxSize, rand() % 101 / 100.0f);
        this->entity->getSprite().setScale(se::Vector2(scale, scale));
        if (rand() % 2)
            this->scaleSpeed *= -1;
    }


    void GooParticleModifier::onUpdate(float elapsedTime)
    {
        if (this->modifier->entity->health <= 0.0f || this->modifier->entity->dead)
        {
            this->entity->dead = true;
        }
        else
        {
            this->entity->getSprite().move(this->modifier->getMidPoint() - this->prevMidPoint);

            this->entity->getSprite().move((this->modifier->getMidPoint() - this->entity->getSprite().getPosition()) * 0.05f * elapsedTime);

            this->entity->getSprite().scale(se::Vector2(1.0f + this->scaleSpeed * elapsedTime, 1.0f + this->scaleSpeed * elapsedTime));
            if (this->entity->getSprite().getScale().x > this->maxSize || this->entity->getSprite().getScale().x < this->minSize)
                this->scaleSpeed *= -1.0f;

            this->entity->getSprite().rotate(this->rotationSpeed * elapsedTime);

            this->prevMidPoint = this->modifier->getMidPoint();
        }
    }


    void GooParticleModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {

    }
}