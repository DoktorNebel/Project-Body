#pragma once

#include "Rectangle.h"
#include "Sprite.h"

namespace bc
{
    extern class Player;
    extern class Projectile;
    extern class Enemy;
    extern class Item;
    extern class LevelElement;

    class IEntity
    {
    public:

        virtual se::Rectangle getHitbox() = 0;
        virtual se::Sprite& getSprite() = 0;
        virtual bool isDead() = 0;
        virtual void hit(Player* otherEntity) = 0;
        virtual void hit(Projectile* otherEntity) = 0;
        virtual void hit(Enemy* otherEntity) = 0;
        virtual void hit(Item* otherEntity) = 0;
        virtual void hit(LevelElement* otherEntity) = 0;
        virtual void update(float elapsedTime) = 0;
    };
}