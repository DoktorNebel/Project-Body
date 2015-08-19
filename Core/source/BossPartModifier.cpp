#include "BossPartModifier.h"

#include <algorithm>

#include "BossModifier.h"
#include "Entity.h"
#include "Content.h"
#include "AnimatedSprite.h"
#include "CoinModifier.h"
#include "AnimationModifier.h"
#include "Spawner.h"
#include "Engine.h"
#include "Camera.h"

namespace bc
{
    BossPartModifier::BossPartModifier(BossModifier* boss, float health, std::string spriteName)
        : boss(boss)
        , health(health)
    {
        this->destroyedSprite = se::Content::getSprite(spriteName + "_Destroyed");
        this->hasDestroyedSprite = this->destroyedSprite.getTextureId() != 0;
    }


    void BossPartModifier::onCreate()
    {
        this->entity->maxHealth = this->health;
        this->entity->health = this->entity->maxHealth;
    }


    void BossPartModifier::onUpdate(float elapsedTime)
    {
        //this->entity->health = 1000.0f;
        if (this->entity->health <= 0.0f)
        {
            if (this->hasDestroyedSprite)
            {
                this->destroyedSprite.setPosition(this->entity->getSprite().getPosition());
                this->entity->sprite = this->destroyedSprite;
            }
            else
            {
                this->boss->destroyPart(this);
            }
            if (!this->destroyed)
            {
                this->destroyed = true;
                this->entity->modifiers.erase(std::find_if(this->entity->modifiers.begin(), this->entity->modifiers.end(), [](IModifier*& modifier)
                {
                    return dynamic_cast<ShootingModifier*>(modifier);
                }));

                for (unsigned int i = 0; i < (unsigned int)this->health; ++i)
                {
                    se::AnimatedSprite coinSprite;
                    coinSprite.addAnimation("Idle");
                    coinSprite.setSpeed("Idle", 0.2f);
                    coinSprite.addSprite("Idle", se::Content::getSprite("M1"));
                    coinSprite.addSprite("Idle", se::Content::getSprite("M2"));
                    coinSprite.addSprite("Idle", se::Content::getSprite("M3"));
                    coinSprite.addSprite("Idle", se::Content::getSprite("M4"));
                    coinSprite.setScale(se::Vector2(3.0f, 3.0f));
                    std::vector<IModifier*> modifiers;
                    modifiers.push_back(new CoinModifier(1));
                    modifiers.push_back(new AnimationModifier(coinSprite));
                    Spawner::spawn(this->entity->getSprite().getPosition(), "M1", modifiers, CollisionGroup::Items);
                }

                this->boss->deleteBullets();

                se::Engine::getActiveCamera().addScreenshake(15.0f, 0.5f);
            }
        }
        if (this->boss->entity->health <= 0.0f)
        {
            this->entity->dead = true;
            this->boss = 0;
        }
    }


    void BossPartModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::PlayerProjectiles && this->boss != 0 && this->entity->health > 0.0f)
        {
            this->boss->entity->health -= otherEntity->damage;
            otherEntity->health -= this->boss->entity->maxHealth;
            if (otherEntity->health <= 0.0f)
                otherEntity->dead = true;
        }
    }
}