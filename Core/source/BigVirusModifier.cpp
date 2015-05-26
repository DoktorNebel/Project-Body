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

    }


    void BigVirusModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->dead)
        {
            for (int i = 0; i < 5; ++i)
            {
                std::vector<IModifier*> modifiers;
                se::AnimatedSprite sprite;
                sprite.addAnimation("Idle");
                sprite.setSpeed("Idle", 0.3f);
                sprite.addAnimation("Death");
                sprite.setSpeed("Death", 0.1f);
                sprite.addSprite("Idle", se::Content::getSprite("Virus1"));
                sprite.addSprite("Idle", se::Content::getSprite("Virus2"));
                sprite.addSprite("Idle", se::Content::getSprite("Virus3"));
                sprite.addSprite("Idle", se::Content::getSprite("Virus4"));
                sprite.addSprite("Death", se::Content::getSprite("VirusDie1"));
                sprite.addSprite("Death", se::Content::getSprite("VirusDie2"));
                sprite.addSprite("Death", se::Content::getSprite("VirusDie3"));
                sprite.addSprite("Death", se::Content::getSprite("VirusDie4"));
                sprite.addSprite("Death", se::Content::getSprite("VirusDie5"));
                sprite.setScale(se::Vector2(1.5f, 1.5f));
                modifiers.push_back(new EnemyModifier(sprite));
                modifiers.push_back(new ShakyMovementModifier());
                modifiers.push_back(new HitMarkerModifier());
                Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 101 - 50, rand() % 101 - 50), "Virus1", modifiers, CollisionGroup::Enemies);
            }
        }
    }


    void BigVirusModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}