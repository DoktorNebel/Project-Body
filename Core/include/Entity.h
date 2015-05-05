#pragma once

#include "Rectangle.h"
#include "Sprite.h"
#include <vector>
#include "IModifier.h"

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
        void hit(Entity* otherEntity);
        void update(float elapsedTime);
    };
}