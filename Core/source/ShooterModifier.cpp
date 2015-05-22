#include "ShooterModifier.h"

#include "Collisiongroup.h"
#include "MathFunctions.h"
#include "Entity.h"
#include "Spawner.h"
#include "ShooterHeadModifier.h"

namespace bc
{
    ShooterModifier::ShooterModifier(std::vector<std::vector<Entity>>* entities)
        : entities(entities)
    {

    }


    void ShooterModifier::onCreate()
    {
        float dist = 1000000.0f;
        se::Vector2 pos;
        for (int i = 0; i < (*this->entities)[CollisionGroup::LevelElements].size(); ++i)
        {
            float newDist;
            if ((newDist = se::Math::Distance(this->entity->getSprite().getPosition(), (*this->entities)[CollisionGroup::LevelElements][i].getSprite().getPosition())) < dist)
            {
                dist = newDist;
                pos = (*this->entities)[CollisionGroup::LevelElements][i].getSprite().getPosition();
            }
        }

        this->entity->getSprite().setRotation(atan2(this->entity->getSprite().getPosition().y - pos.y, this->entity->getSprite().getPosition().x - pos.x) * 57.2957795f);

        std::vector<IModifier*> modifiers;
        modifiers.push_back(new ShooterHeadModifier(this->entities, this));
        Spawner::spawn(this->entity->getSprite().getPosition(), "ShooterHead", modifiers, CollisionGroup::Enemies);
    }


    void ShooterModifier::onUpdate(float elapsedTime)
    {

    }


    void ShooterModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}