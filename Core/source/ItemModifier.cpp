#include "ItemModifier.h"

#include "Entity.h"
#include "PlayerModifier.h"
#include "MathFunctions.h"
#include "GameData.h"
#include "Content.h"
#include "PlayerShootingModifier.h"
#include "NormalShootingModifier.h"
#include "SplitShootingModifier.h"
#include "HomingShootingModifier.h"
#include "CurvyShootingModifier.h"
#include "LaserShootingModifier.h"

namespace bc
{
    ItemModifier::ItemModifier(Effect::Type effect)
        : effect(effect)
    {

    }


    void ItemModifier::onCreate()
    {
        se::Vector2 position = this->entity->getSprite().getPosition();
        this->sprite.addAnimation("Idle");
        this->sprite.setSpeed("Idle", 0.2f);
        switch (this->effect)
        {
        case Effect::Upgrade:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpX2_5"));
            break;

        case Effect::Normal:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpNormal_5"));
            break;

        case Effect::Split:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpSplit_5"));
            break;

        case Effect::Curvy:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_5"));
            break;

        case Effect::Homing:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpCurvy_5"));
            break;

        case Effect::Laser:
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_0"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_1"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_2"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_3"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_4"));
            this->sprite.addSprite("Idle", se::Content::getSprite("PowerUpLaser_5"));
            break;
        }
        this->sprite.setPosition(position);
        this->sprite.setScale(se::Vector2(2.0f, 2.0f));
    }


    void ItemModifier::onUpdate(float elapsedTime)
    {
        this->sprite.move(se::Vector2(0.0f, -100.0f) * elapsedTime);
        this->sprite.update(elapsedTime);

        this->entity->sprite = this->sprite.getCurrentSprite();
    }


    void ItemModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::Players && !this->entity->dead)
        {
            unsigned int index = 0;
            while (index < otherEntity->modifiers.size() && !dynamic_cast<PlayerShootingModifier*>(otherEntity->modifiers[index]))
            {
                ++index;
            }
            PlayerShootingModifier* playerShooting = (PlayerShootingModifier*)otherEntity->modifiers[index];
            int level = playerShooting->getLevel();

            switch (this->effect)
            {
            case Effect::Upgrade:
                playerShooting->upgrade();
                break;

            case Effect::Normal:
                delete playerShooting;
                otherEntity->modifiers.erase(otherEntity->modifiers.begin() + index);
                otherEntity->modifiers.push_back(new NormalShootingModifier(level));
                break;

            case Effect::Split:
                delete playerShooting;
                otherEntity->modifiers.erase(otherEntity->modifiers.begin() + index);
                otherEntity->modifiers.push_back(new SplitShootingModifier(level));
                break;


            case Effect::Curvy:
                delete playerShooting;
                otherEntity->modifiers.erase(otherEntity->modifiers.begin() + index);
                otherEntity->modifiers.push_back(new CurvyShootingModifier(level));
                break;


            case Effect::Homing:
                delete playerShooting;
                otherEntity->modifiers.erase(otherEntity->modifiers.begin() + index);
                otherEntity->modifiers.push_back(new HomingShootingModifier(level));
                break;


            case Effect::Laser:
                otherEntity->modifiers.erase(otherEntity->modifiers.begin() + index);
                otherEntity->modifiers.push_back(new LaserShootingModifier(level));
                break;
            }

            this->entity->dead = true;
        }
    }
}