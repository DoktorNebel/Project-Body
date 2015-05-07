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
        this->entity->health = 100.0f;
        this->entity->maxHealth = 100.0f;
        this->animatedSprite.setScale(se::Vector2(1.5f, 1.5f));
        this->animatedSprite.setPosition(this->entity->getSprite().getPosition());
    }


    void EnemyModifier::onUpdate(float elapsedTime)
    {
        this->animatedSprite.update(elapsedTime);

        if (this->entity->health <= 0.0f)
        {
            if (this->animatedSprite.getCurrentAnimation() != "Death")
            {
                se::Engine::getActiveCamera().addScreenshake(1.0f * this->entity->maxHealth / 200.0f, 0.05f * this->entity->maxHealth / 200.0f);
                for (int i = 0; i < this->entity->maxHealth / 4; ++i)
                {
                    std::vector<IModifier*> modifiers;
                    modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                    Spawner::spawn(this->entity->getSprite().getPosition(), Entity(se::Content::getSprite("Funke1"), modifiers), CollisionGroup::Particles);
                }
                this->animatedSprite.changeAnimation("Death");
            }

            if (this->animatedSprite.finishedAnimation())
                this->entity->dead = true;
        }
        else
        {
            this->animatedSprite.move(se::Vector2(0.0f, -100.0f * elapsedTime));
            if (this->animatedSprite.getPosition().y < -(int)se::Engine::getSettings().resolutionHeight / 2)
                this->entity->dead = true;
        }

        this->entity->sprite = this->animatedSprite.getCurrentSprite();
    }


    void EnemyModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        otherEntity->health -= this->entity->maxHealth / 5.0f;
    }
}