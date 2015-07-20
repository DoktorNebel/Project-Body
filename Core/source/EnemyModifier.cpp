#include "EnemyModifier.h"

#include "Entity.h"
#include "Engine.h"
#include "ParticleModifier.h"
#include "AnimatedSprite.h"
#include "AnimationModifier.h"
#include "Spawner.h"
#include "ItemModifier.h"
#include "GameData.h"
#include "MathFunctions.h"

namespace bc
{
    EnemyModifier::EnemyModifier(se::AnimatedSprite animatedSprite, unsigned int score, float humanInfection)
        : animatedSprite(animatedSprite)
        , position(0.0f, 0.0f)
        , score(score)
        , humanInfection(humanInfection)
        , lastHit(CollisionGroup::Enemies)
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
        this->animatedSprite.setRotation(this->entity->getSprite().getRotation());
        this->animatedSprite.setColor(this->entity->getSprite().getColor());

        if (this->entity->health <= 0.0f)
        {
            if (this->animatedSprite.getCurrentAnimation() != "Death")
            {
                if (this->lastHit == CollisionGroup::PlayerProjectiles)
                {
                    float shakeStrength = se::Math::Clamp(1.0f, 20.0f, this->entity->maxHealth / 20.0f);
                    float shakeDuration = se::Math::Clamp(0.1f, 2.0f, 0.05f * this->entity->maxHealth / 20.0f);
                    se::Engine::getActiveCamera().addScreenshake(shakeStrength, shakeDuration);
                    int particleCount = (int)se::Math::Clamp(50.0f, 500.0f, this->entity->maxHealth * 2.0f);
                    for (int i = 0; i < particleCount; ++i)
                    {
                        float lifeTime = se::Math::Clamp(1.0f, 5.0f, rand() % 2001 / 1000.0f * (this->entity->maxHealth / 10.0f));
                        std::vector<IModifier*> modifiers;
                        modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), se::Vector2(2.5f, 2.5f), lifeTime));
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

                    if (this->golden)
                    {
                        std::vector<IModifier*> modifiers;
                        modifiers.push_back(new ItemModifier(this->dropType));
                        Spawner::spawn(this->entity->getSprite().getPosition(), "ITEM1", modifiers, CollisionGroup::Items);
                    }

                    GameData::addScore(this->score);
                }
                else
                {
                    GameData::humanInfection += this->humanInfection;
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
        this->lastHit = collisionGroup;

        if (collisionGroup != CollisionGroup::LevelElements && this->entity->health > 0.0f)
            otherEntity->health -= this->entity->maxHealth / 5.0f;
    }
}