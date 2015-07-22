#include "BoogerModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Spawner.h"
#include "ParticleModifier.h"

namespace bc
{
    void BoogerModifier::onCreate()
    {
        this->direction = se::Vector2(0.0f, 0.0f);
        this->speed = 0.0f;
    }


    void BoogerModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->direction * this->speed * elapsedTime);
    }


    void BoogerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::PlayerProjectiles)
        {
            this->direction += se::Vector2(projectionVector.x, 0.0f) / 5.0f;
            se::Math::Normalize(this->direction);
            this->speed += projectionScalar / 10.0f;
        }

        if (collisionGroup == CollisionGroup::LevelElements || collisionGroup == CollisionGroup::ScrollingEnemies)
        {
            this->direction = this->direction - projectionVector * se::Math::Dot(this->direction, projectionVector) * 2.0f;
            this->speed -= projectionScalar;
            if (this->direction == se::Vector2(0.0f, 0.0f))
                this->direction = projectionVector;
        }

        if (this->speed > 300.0f)
            this->speed = 300.0f;
    }
}