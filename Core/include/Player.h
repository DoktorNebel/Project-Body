#pragma once

#include "IEntity.h"
#include "Vector2.h"
#include "Sprite.h"

namespace bc
{
    class Player : public IEntity
    {
    private:

        float maxHealth;
        float health;
        float speed;
        se::Sprite sprite;

    public:

        Player();
        ~Player();

    public:

        virtual se::Rectangle getHitbox();
        virtual se::Sprite& getSprite();
        virtual bool isDead();
        virtual void hit(Player* otherEntity);
        virtual void hit(Projectile* otherEntity);
        virtual void hit(Enemy* otherEntity);
        virtual void hit(Item* otherEntity);
        virtual void hit(LevelElement* otherEntity);
        virtual void update(float elapsedTime);
    };
}