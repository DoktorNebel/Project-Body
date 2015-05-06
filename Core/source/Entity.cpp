#include "Entity.h"

namespace bc
{
    Entity::Entity()
    {

    }


    Entity::Entity(const Entity& other)
        : health(other.health)
        , maxHealth(other.maxHealth)
        , sprite(other.sprite)
        , modifiers(other.modifiers)
    {
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->entity = this;
            this->modifiers[i]->onCreate();
        }
    }


    Entity::Entity(se::Sprite sprite, std::vector<IModifier*> modifiers)
        : health(100.0f)
        , maxHealth(100.0f)
        , sprite(sprite)
        , modifiers(modifiers)
    {
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->entity = this;
            this->modifiers[i]->onCreate();
        }
    }


    Entity::~Entity()
    {

    }


    se::Rectangle Entity::getHitbox()
    {
        return this->sprite.getRect();
    }


    se::Sprite& Entity::getSprite()
    {
        return this->sprite;
    }


    bool Entity::isDead()
    {
        return this->health <= 0.0f;
    }


    void Entity::hit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->onHit(otherEntity, collisionGroup);
        }
    }


    void Entity::update(float elapsedTime)
    {
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->entity = this;
        }
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->onUpdate(elapsedTime);
        }
    }
}