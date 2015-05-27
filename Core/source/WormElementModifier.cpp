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
        , spawned(false)
        , stopped(false)
    {

    }


    void WormElementModifier::stop()
    {
        this->stopped = true;

        delete this->entity->modifiers.back();
        this->entity->modifiers.pop_back();
        if (this->nextElement != 0 && !this->nextElement->stopped)
            this->nextElement->stop();
        if (this->previousElement != 0 && !this->previousElement->stopped)
            this->previousElement->stop();
    }


    void WormElementModifier::onCreate()
    {
        this->spawnPos = this->entity->getSprite().getPosition();
        this->entity->health = 50.0f;
        this->entity->maxHealth = 50.0f;
    }


    void WormElementModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->health <= 0.0f && !this->stopped)
            this->stop();

        if (this->entity->dead)
        {
            if (this->nextElement != 0)
            {
                this->nextElement->entity->health = 0.0f;
                this->nextElement->previousElement = 0;
                this->nextElement = 0;
            }

            if (this->previousElement != 0)
            {
                this->previousElement->entity->health = 0.0f;
                this->previousElement->nextElement = 0;
                this->previousElement = 0;
            }
        }
        else if (!this->spawned && this->elementNum != 0 && se::Math::Distance(this->entity->getSprite().getPosition(), this->spawnPos) >= 40.0f)
        {
            this->spawned = true;

            //std::string spriteName = this->elementNum == 1 ? "Worm_Tail" : "Worm_Body";
            std::vector<IModifier*> modifiers;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.05f);
            sprite.addAnimation("Death");
            sprite.setSpeed("Death", 0.05f);
            sprite.addSprite("Idle", se::Content::getSprite("Neurax1"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax2"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax3"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax4"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax5"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax6"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax7"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax8"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax9"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax10"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax11"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax12"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax13"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax14"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_1"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_2"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_3"));
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            sprite.setDepth(-(this->elementNum - 1) / 10.0f);
            modifiers.push_back(new EnemyModifier(sprite));
            modifiers.push_back(new WormElementModifier(false, this->elementNum - 1, this));
            this->nextElement = (WormElementModifier*)modifiers.back();
            modifiers.push_back(new HitMarkerModifier());
            modifiers.push_back(new MovementPatternModifier(*(MovementPatternModifier*)this->entity->modifiers.back()));
            Spawner::spawn(this->spawnPos, "Neurax1", modifiers, CollisionGroup::Enemies);
        }
    }


    void WormElementModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}