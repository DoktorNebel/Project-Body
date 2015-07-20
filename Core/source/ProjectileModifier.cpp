#include "ProjectileModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"
#include "ParticleModifier.h"
#include "AnimatedSprite.h"
#include "AnimationModifier.h"

namespace bc
{
    ProjectileModifier::ProjectileModifier(se::Vector2 velocity, float lifeTime)
        : direction(velocity)
        , speed(se::Math::Length(velocity))
        , lifeTime(lifeTime)
    {
        if (this->speed != 0.0f)
            se::Math::Normalize(this->direction);
    }


    ProjectileModifier::~ProjectileModifier()
    {

    }


    void ProjectileModifier::onCreate()
    {
        this->entity->getSprite().setDepth(-0.1f);
        this->entity->getSprite().setScale(se::Vector2(1.5f, 1.5f));
        this->entity->getSprite().setRotation(atan2(this->direction.x, this->direction.y) * -57.2957795f);
        this->entity->damage = 1.0f;
    }


    void ProjectileModifier::onUpdate(float elapsedTime)
    {
        if (this->speed != 0.0f)
            this->entity->getSprite().setRotation(atan2(this->direction.x, this->direction.y) * -57.2957795f);
        this->entity->getSprite().move(this->direction * this->speed * elapsedTime);
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->dead = true;
    }


    void ProjectileModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::LevelElements)
        {
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new ParticleModifier(this->direction * -500.0f + se::Vector2(rand() % 1001 - 500, rand() % 1001 - 500), se::Vector2(2.5f, 2.5f), rand() % 1501 / 1000.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Funke1", modifiers, CollisionGroup::Particles);

            modifiers.clear();
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.01f);
            sprite.addSprite("Idle", se::Content::getSprite("Flare1"));
            sprite.addSprite("Idle", se::Content::getSprite("Flare2"));
            sprite.addSprite("Idle", se::Content::getSprite("Flare3"));
            modifiers.push_back(new ParticleModifier(se::Vector2(0.0f, 0.0f), se::Vector2(0.5f, 0.5f), 0.15f));
            modifiers.push_back(new AnimationModifier(sprite));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Flare1", modifiers, CollisionGroup::Particles);

            this->entity->dead = true;
        }
        if (otherEntity->health > 0.0f)
        {
            otherEntity->health -= this->entity->damage;

            this->entity->dead = true;
        }
    }
}