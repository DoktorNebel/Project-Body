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
        switch (this->effect)
        {
        case Effect::Upgrade:
            this->entity->sprite = se::Content::getSprite("ITEM5");
            break;

        case Effect::Normal:
            this->entity->sprite = se::Content::getSprite("ITEM1");
            break;

        case Effect::Split:
            this->entity->sprite = se::Content::getSprite("ITEM3");
            break;

        case Effect::Curvy:
            this->entity->sprite = se::Content::getSprite("ITEM2");
            break;

        case Effect::Homing:
            this->entity->sprite = se::Content::getSprite("ITEM2");
            break;

        case Effect::Laser:
            this->entity->sprite = se::Content::getSprite("ITEM4");
            break;
        }
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
    }


    void ItemModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(se::Vector2(0.0f, -100.0f) * elapsedTime);
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
                otherEntity->modifiers.push_back(new LaserShootingModifier(playerShooting));
                break;
            }

            this->entity->dead = true;
        }
    }
}