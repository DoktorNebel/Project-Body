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
        , hitMarkerTime(0.005f)
        , timer(0.0f)
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

        if (this->entity->health <= 0.0f)
        {
            if (this->animatedSprite.getCurrentAnimation() != "Death")
            {
                se::Engine::getActiveCamera().addScreenshake(1.0f * this->entity->maxHealth / 200.0f, 0.05f * this->entity->maxHealth / 200.0f);
                int minParticles = this->entity->maxHealth / 4;
                minParticles = minParticles < 20 ? 20 : minParticles;
                for (int i = 0; i < minParticles; ++i)
                {
                    std::vector<IModifier*> modifiers;
                    modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                    Spawner::spawn(this->entity->getSprite().getPosition(), Entity(se::Content::getSprite("Funke1"), modifiers), CollisionGroup::Particles);
                }
                this->animatedSprite.changeAnimation("Death");
            }

            if (this->animatedSprite.finishedAnimation())
                this->entity->dead = true;
            else
                this->entity->sprite = this->animatedSprite.getCurrentSprite();
        }
        else
        {
            this->animatedSprite.move(se::Vector2(0.0f, -100.0f * elapsedTime));
            if (this->animatedSprite.getPosition().y < -(int)se::Engine::getSettings().resolutionHeight / 2)
                this->entity->dead = true;
            this->entity->sprite = this->animatedSprite.getCurrentSprite();
        }

        this->timer += elapsedTime;
        if (this->timer >= this->hitMarkerTime)
        {
            this->animatedSprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        }
        else
        {
            this->animatedSprite.setColor(this->entity->getSprite().getColor());
        }
    }


    void EnemyModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        this->animatedSprite.setColor(se::Vector4(3.0f, 3.0f, 3.0f, 1.0f));
        this->timer = 0.0f;
        if (this->entity->health > 0.0f)
            otherEntity->health -= this->entity->maxHealth / 5.0f;
    }
}