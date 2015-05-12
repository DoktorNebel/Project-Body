#include "Entity.h"

namespace bc
{
    Entity::Entity()
    {

    }


    Entity::Entity(const Entity& other)
        : id(other.id)
        , health(other.health)
        , maxHealth(other.maxHealth)
        , damage(other.damage)
        , dead(other.dead)
        , sprite(other.sprite)
        , modifiers(other.modifiers)
    {

    }


    Entity::Entity(se::Sprite sprite, std::vector<IModifier*> modifiers)
        : id(0)
        , health(100.0f)
        , maxHealth(100.0f)
        , damage(10.0f)
        , dead(false)
        , sprite(sprite)
        , modifiers(modifiers)
    {

    }


    Entity::~Entity()
    {

    }


    Entity& Entity::operator=(const Entity& rhs)
    {
        this->id = rhs.id;
        this->health = rhs.health;
        this->maxHealth = rhs.maxHealth;
        this->damage = rhs.damage;
        this->dead = rhs.dead;
        this->sprite = rhs.sprite;
        this->modifiers = rhs.modifiers;

        return *this;
    }


    bool Entity::operator==(const Entity& rhs)
    {
        return this->id == rhs.id;
    }


    void Entity::init()
    {
        for (int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->entity = this;
            this->modifiers[i]->onCreate();
        }
    }


    se::Rectangle Entity::getHitbox()
    {
        return this->sprite.getRect();
    }


    se::Sprite& Entity::getSprite()
    {
        return this->sprite;
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
            this->modifiers[i]->onUpdate(elapsedTime);
        }
    }


    void Entity::destroy()
    {
        while (this->modifiers.size() > 0)
        {
            delete this->modifiers.back();
            this->modifiers.pop_back();
        }
    }
}