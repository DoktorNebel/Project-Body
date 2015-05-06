#include "ProjectileModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "Spawner.h"
#include "ParticleModifier.h"

namespace bc
{
    ProjectileModifier::ProjectileModifier(se::Vector2(velocity), float lifeTime)
        : velocity(velocity)
        , lifeTime(lifeTime)
    {

    }


    ProjectileModifier::~ProjectileModifier()
    {

    }


    void ProjectileModifier::onCreate()
    {
        this->entity->getSprite().setRotation(atan2(this->velocity.x, this->velocity.y) * -57.2957795f);
        this->entity->getSprite().setDepth(1.0f);
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
    }


    void ProjectileModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(this->velocity * elapsedTime);
        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f)
            this->entity->health = 0.0f;
    }


    void ProjectileModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        otherEntity->health -= 10.0f;
        if (otherEntity->health <= 0.0f)
        {
            se::Engine::getActiveCamera().addScreenshake(1.0f * otherEntity->maxHealth / 200.0f, 0.05f * otherEntity->maxHealth / 200.0f);
            for (int i = 0; i < otherEntity->maxHealth / 4; ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                Spawner::spawn(otherEntity->getSprite().getPosition(), Entity(se::Content::getSprite("Funke1"), modifiers), CollisionGroup::Particles);
            }
        }
        this->entity->health = 0.0f;
    }
}