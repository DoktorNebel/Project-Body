#include "WormElementModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Spawner.h"
#include "EnemyModifier.h"
#include "Content.h"
#include "HitMarkerModifier.h"

namespace bc
{
    WormElementModifier::WormElementModifier(bool head, int length, WormElementModifier* previousElement)
        : head(head)
        , elementNum(length)
        , nextElement(0)
        , previousElement(previousElement)
    {

    }


    void WormElementModifier::onCreate()
    {
        this->spawnPos = this->entity->getSprite().getPosition();
    }


    void WormElementModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->dead)
        {
            if (this->nextElement != 0)
            {
                this->nextElement->entity->health = 0.0f;
                this->nextElement = 0;
            }

            if (this->previousElement != 0)
            {
                this->previousElement->entity->health = 0.0f;
                this->previousElement = 0;
            }
        }
        else
        {
            if (this->nextElement != 0 && this->nextElement->entity->health <= 0.0f)
                this->nextElement = 0;

            if (this->previousElement != 0 && this->previousElement->entity->health <= 0.0f)
                this->previousElement = 0;
        }

        if (this->nextElement == 0 && this->elementNum != 0 && se::Math::Distance(this->entity->getSprite().getPosition(), this->spawnPos) >= 40.0f)
        {
            std::vector<IModifier*> modifiers;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.3f);
            sprite.addAnimation("Death");
            sprite.setSpeed("Death", 0.3f);
            sprite.addSprite("Idle", se::Content::getSprite("Worm_Body"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_1"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_2"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_3"));
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            modifiers.push_back(new EnemyModifier(sprite));
            modifiers.push_back(new WormElementModifier(false, this->elementNum - 1, this));
            this->nextElement = (WormElementModifier*)modifiers.back();
            modifiers.push_back(new HitMarkerModifier());
            modifiers.push_back(new MovementPatternModifier(*(MovementPatternModifier*)this->entity->modifiers.back()));
            Spawner::spawn(this->spawnPos, "Worm_Body", modifiers, CollisionGroup::Enemies);
        }
    }


    void WormElementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}