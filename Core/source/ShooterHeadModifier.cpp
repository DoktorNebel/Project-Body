#include "ShooterHeadModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "ProjectileModifier.h"
#include "Spawner.h"
#include "ShooterModifier.h"
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
        this->entity->getSprite().scale(se::Vector2(1.5f, 1.5f));
    }


    void ShooterHeadModifier::onUpdate(float elapsedTime)
    {
        float dist = 1000000.0f;
        se::Vector2 pos;
        for (int i = 0; i < (*this->entities)[CollisionGroup::Players].size(); ++i)
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
            Spawner::spawn(this->entity->getSprite().getPosition(), "EnemyShoot1", modifiers, CollisionGroup::EnemyProjectiles);
        }

        if (this->entity->health <= 0.0f || this->entity->getSprite().getPosition().x < -50 || this->entity->getSprite().getPosition().x > se::Engine::getSettings().resolutionWidth + 50 ||
            this->entity->getSprite().getPosition().y < -50 || this->entity->getSprite().getPosition().y > se::Engine::getSettings().resolutionHeight + 50)
        {
            this->entity->dead = true;
            this->shooter->entity->dead = true;
        }
    }


    void ShooterHeadModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}