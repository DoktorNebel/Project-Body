#include "EnemyModifier.h"

#include "Entity.h"
#include "Engine.h"
#include "ParticleModifier.h"
#include "Spawner.h"

namespace bc
{
    EnemyModifier::EnemyModifier(se::AnimatedSprite animatedSprite)
        : animatedSprite(animatedSprite)
        , position(0.0f, 0.0f)
    {

    }


    EnemyModifier::~EnemyModifier()
    {

    }


    void EnemyModifier::onCreate()
    {
        this->animatedSprite.setPosition(this->entity->getSprite().getPosition());
    }


    void EnemyModifier::onUpdate(float elapsedTime)
    {
        this->animatedSprite.update(elapsedTime);

        this->animatedSprite.setPosition(this->entity->getSprite().getPosition());
        this->animatedSprite.setColor(this->entity->getSprite().getColor());

        if (this->entity->health <= 0.0f)
        {
            if (this->animatedSprite.getCurrentAnimation() != "Death")
            {
                se::Engine::getActiveCamera().addScreenshake(1.0f * this->entity->maxHealth / 20.0f, 0.05f * this->entity->maxHealth / 20.0f);
                int particleCount = this->entity->maxHealth;
                particleCount = particleCount < 20 ? 20 : particleCount;
                particleCount = particleCount > 200 ? 200 : particleCount;
                for (int i = 0; i < particleCount; ++i)
                {
                    std::vector<IModifier*> modifiers;
                    modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                    Spawner::spawn(this->entity->getSprite().getPosition(), "Funke1", modifiers, CollisionGroup::Particles);
                }

                if (!this->animatedSprite.changeAnimation("Death"))
                    this->entity->dead = true;
            }

            if (this->animatedSprite.finishedAnimation())
                this->entity->dead = true;
            else
                this->entity->sprite = this->animatedSprite.getCurrentSprite();
        }
        else
        {
            this->entity->sprite = this->animatedSprite.getCurrentSprite();
        }
    }


    void EnemyModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (this->entity->health > 0.0f)
            otherEntity->health -= this->entity->maxHealth / 5.0f;
    }
}