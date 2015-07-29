#include "BigVirusModifier.h"

#include "Entity.h"
#include "Spawner.h"
#include "ShakyMovementModifier.h"
#include "HitMarkerModifier.h"
#include "MathFunctions.h"
#include "AnimatedSprite.h"
#include "Content.h"
#include "EnemyModifier.h"

namespace bc
{
    void BigVirusModifier::onCreate()
    {
        this->lastHit = CollisionGroup::Enemies;
    }


    void BigVirusModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->dead && this->lastHit == CollisionGroup::PlayerProjectiles)
        {
            for (int i = 0; i < 5; ++i)
            {
                std::vector<IModifier*> modifiers;
                se::AnimatedSprite sprite;
                sprite.addAnimation("Idle");
                sprite.setSpeed("Idle", 0.3f);
                sprite.addSprite("Idle", se::Content::getSprite("Vverkleinert1"));
                sprite.addSprite("Idle", se::Content::getSprite("Vverkleinert2"));
                sprite.addSprite("Idle", se::Content::getSprite("Vverkleinert3"));
                sprite.addSprite("Idle", se::Content::getSprite("Vverkleinert4"));
                sprite.setScale(se::Vector2(1.0f, 1.0f));
                modifiers.push_back(new EnemyModifier(sprite, 2, 0.02f));
                modifiers.push_back(new ShakyMovementModifier());
                modifiers.push_back(new HitMarkerModifier());
                Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 101 - 50, rand() % 101 - 50), "Virus1", modifiers, CollisionGroup::Enemies);
            }
        }
    }


    void BigVirusModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup != CollisionGroup::LevelElements)
            this->lastHit = collisionGroup;
    }
}