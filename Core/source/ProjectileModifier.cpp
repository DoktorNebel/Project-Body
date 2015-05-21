#include "ProjectileModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"
#include "ParticleModifier.h"

namespace bc
{
    ProjectileModifier::ProjectileModifier(se::Vector2 velocity, float lifeTime)
        : direction(se::Math::GetNormalized(velocity))
        , speed(se::Math::Length(velocity))
        , lifeTime(lifeTime)
    {

    }


    ProjectileModifier::~ProjectileModifier()
    {

    }


    void ProjectileModifier::onCreate()
    {
        //this->lifeTime = 10.0f;
        //this->speed = 100.0f;
        this->entity->getSprite().setDepth(0.1f);
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
        this->entity->damage = 1.0f;
    }


    void ProjectileModifier::onUpdate(float elapsedTime)
    {
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
            modifiers.push_back(new ParticleModifier(this->direction * -0.5f + se::Vector2(rand() % 1501 - 750, rand() % 1501 - 750), rand() % 501 / 2000.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Funke1", modifiers, CollisionGroup::Particles);

            this->entity->dead = true;
        }
        if (otherEntity->health > 0.0f)
        {
            otherEntity->health -= this->entity->damage;

            this->entity->dead = true;
        }
    }
}