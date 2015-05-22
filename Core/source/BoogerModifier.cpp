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
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
    }


    void BoogerModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->direction * this->speed * elapsedTime);
        if (this->entity->health <= 0.0f)
        {
            int particleCount = this->entity->maxHealth;
            particleCount = particleCount < 20 ? 20 : particleCount;
            particleCount = particleCount > 200 ? 200 : particleCount;
            for (int i = 0; i < particleCount; ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                Spawner::spawn(this->entity->getSprite().getPosition(), "Funke1", modifiers, CollisionGroup::Particles);
            }

            this->entity->dead = true;
        }
    }


    void BoogerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::PlayerProjectiles)
        {
            this->direction += se::Vector2(projectionVector.x, 0.0f) / 5.0f;
            se::Math::Normalize(this->direction);
            this->speed += projectionScalar / 10.0f;
        }

        if (collisionGroup == CollisionGroup::LevelElements)
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