#pragma once

#include "Rectangle.h"
#include "Sprite.h"
#include <vector>
#include "IModifier.h"
#include "Collisiongroup.h"

namespace bc
{
    class Entity
    {
    public:

        float maxHealth;
        float health;
        se::Sprite sprite;
        std::vector<IModifier*> modifiers;

    public:

        Entity();
        Entity(const Entity& other);
        Entity(se::Sprite sprite, std::vector<IModifier*> modifiers);
        ~Entity();

    public:

        se::Rectangle getHitbox();
        se::Sprite& getSprite();
        bool isDead();
        void hit(Entity* otherEntity, CollisionGroup::Type collisionGroup);
        void update(float elapsedTime);
    };
}