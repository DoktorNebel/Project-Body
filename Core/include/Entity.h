#pragma once

#include "Rectangle.h"
#include "Sprite.h"
#include <vector>
#include "IModifier.h"
#include "Collisiongroup.h"
#include "Polygon.h"

namespace bc
{
    class Entity
    {
    public:

        unsigned int id;
        float maxHealth;
        float health;
        float damage;
        bool dead;
        se::Sprite sprite;
        se::Polygon hitbox;
        std::vector<IModifier*> modifiers;

    public:

        Entity();
        Entity(const Entity& other);
        Entity(se::Sprite sprite, std::vector<IModifier*> modifiers);
        ~Entity();

    public:

        Entity& operator=(const Entity& rhs);
        bool operator==(const Entity& rhs);

    public:

        void init();
        se::Rectangle getHitRect();
        se::Polygon& getHitbox();
        se::Sprite& getSprite();
        void hit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
        void update(float elapsedTime);
        void destroy();
    };
}