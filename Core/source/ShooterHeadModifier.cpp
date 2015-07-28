#include "ShooterHeadModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "ProjectileModifier.h"
#include "Spawner.h"
#include "ShooterModifier.h"
#include "ParticleModifier.h"
#include "AnimatedSprite.h"
#include "AnimationModifier.h"
#include "Engine.h"

namespace bc
{
    ShooterHeadModifier::ShooterHeadModifier(std::vector<std::vector<Entity>>* entities, ShooterModifier* shooter)
        : entities(entities)
        , fireRate(1.0f)
        , timer(0.0f)
        , shooter(shooter)
    {

    }


    void ShooterHeadModifier::onCreate()
    {
        this->entity->getSprite().scale(se::Vector2(1.0f, 1.0f));
    }


    void ShooterHeadModifier::onUpdate(float elapsedTime)
    {
        float dist = 1000000.0f;
        se::Vector2 pos;
        for (unsigned int i = 0; i < (*this->entities)[CollisionGroup::Players].size(); ++i)
        {
            float newDist;
            if ((newDist = se::Math::Distance(this->entity->getSprite().getPosition(), (*this->entities)[CollisionGroup::Players][i].getSprite().getPosition())) < dist)
            {
                dist = newDist;
                pos = (*this->entities)[CollisionGroup::Players][i].getSprite().getPosition();
            }
        }

        this->entity->getSprite().setRotation(atan2(pos.y - this->entity->getSprite().getPosition().y, pos.x - this->entity->getSprite().getPosition().x) * 57.2957795f - 90.0f);

        this->timer += elapsedTime;
        if (this->timer >= this->fireRate)
        {
            this->timer = 0.0f;
            std::vector<IModifier*> modifiers;
            se::Vector2 velocity(cos((this->entity->getSprite().getRotation() + 90.0f) * 0.0174532925f), sin((this->entity->getSprite().getRotation() + 90.0f) * 0.0174532925f));
            modifiers.push_back(new ProjectileModifier(velocity * 500.0f, 5.0f));
            Spawner::spawn(this->entity->getSprite().getPosition() + velocity * 20.0f, "EnemyShoot1", modifiers, CollisionGroup::EnemyProjectiles);
        }

        if (this->entity->health <= 0.0f || this->entity->getSprite().getPosition().x + 50.0f < (float)se::Engine::getSettings().renderResolutionWidth / -2.0f || this->entity->getSprite().getPosition().x - 50.0f > (float)se::Engine::getSettings().renderResolutionWidth / 2.0f ||
            this->entity->getSprite().getPosition().y + 50.0f < (float)se::Engine::getSettings().renderResolutionHeight / -2.0f || this->entity->getSprite().getPosition().y - 50.0f > (float)se::Engine::getSettings().renderResolutionHeight / 2.0f)
        {
            se::Engine::getActiveCamera().addScreenshake(1.0f * this->entity->maxHealth / 20.0f, 0.05f * this->entity->maxHealth / 20.0f);
            int particleCount = (int)this->entity->maxHealth;
            particleCount = particleCount < 20 ? 20 : particleCount;
            particleCount = particleCount > 200 ? 200 : particleCount;
            for (int i = 0; i < particleCount; ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), se::Vector2(2.0f, 2.0f), rand() % 1001 / 1000.0f));
                Spawner::spawn(this->entity->getSprite().getPosition(), "Funke1", modifiers, CollisionGroup::Particles);
            }

            std::vector<IModifier*> modifiers;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.05f);
            sprite.addSprite("Idle", se::Content::getSprite("Flare1"));
            sprite.addSprite("Idle", se::Content::getSprite("Flare2"));
            sprite.addSprite("Idle", se::Content::getSprite("Flare3"));
            modifiers.push_back(new ParticleModifier(se::Vector2(0.0f, 0.0f), se::Vector2(1.0f, 1.0f), 0.15f));
            modifiers.push_back(new AnimationModifier(sprite));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Flare1", modifiers, CollisionGroup::Particles);

            this->entity->dead = true;
            if (this->shooter)
            {
                this->shooter->entity->dead = true;
                this->shooter = 0;
            }
        }
    }


    void ShooterHeadModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}