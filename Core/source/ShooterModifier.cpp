#include "ShooterModifier.h"

#include "Collisiongroup.h"
#include "MathFunctions.h"
#include "Entity.h"
#include "Spawner.h"
#include "ShooterHeadModifier.h"
#include "HitMarkerModifier.h"
#include "EnemyModifier.h"
#include "AnimatedSprite.h"
#include "Content.h"

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
        for (unsigned int i = 0; i < (*this->entities)[CollisionGroup::LevelElements].size(); ++i)
        {
            float newDist;
            if ((newDist = se::Math::Distance(this->entity->getSprite().getPosition(), (*this->entities)[CollisionGroup::LevelElements][i].getSprite().getPosition())) < dist)
            {
                dist = newDist;
                pos = (*this->entities)[CollisionGroup::LevelElements][i].getSprite().getPosition();
            }
        }

        this->entity->getSprite().setRotation(atan2(pos.y - this->entity->getSprite().getPosition().y, pos.x - this->entity->getSprite().getPosition().x) * 57.2957795f + 90.0f);

        std::vector<IModifier*> modifiers;
        se::AnimatedSprite sprite;
        sprite.addAnimation("Idle");
        sprite.setSpeed("Idle", 1.0f);
        sprite.addSprite("Idle", se::Content::getSprite("ShooterHead"));
        modifiers.push_back(new EnemyModifier(sprite, 200, 0.01f));
        modifiers.push_back(new ShooterHeadModifier(this->entities, this));
        modifiers.push_back(new HitMarkerModifier());
        Spawner::spawn(this->entity->getSprite().getPosition(), "ShooterHead", modifiers, CollisionGroup::ScrollingEnemies);
    }


    void ShooterModifier::onUpdate(float elapsedTime)
    {

    }


    void ShooterModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}