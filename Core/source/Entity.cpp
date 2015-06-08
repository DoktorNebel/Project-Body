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
        , hitbox(other.hitbox)
        , modifiers(other.modifiers)
    {

    }


    Entity::Entity(se::Sprite sprite, std::vector<IModifier*> modifiers)
        : id(0)
        , health(1.0f)
        , maxHealth(1.0f)
        , damage(1.0f)
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
        this->hitbox = rhs.hitbox;
        this->modifiers = rhs.modifiers;

        return *this;
    }


    bool Entity::operator==(const Entity& rhs)
    {
        return this->id == rhs.id;
    }


    void Entity::init()
    {
        for (unsigned int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->entity = this;
            this->modifiers[i]->onCreate();
        }
    }


    se::Rectangle Entity::getHitRect()
    {
        return this->sprite.getRect();
    }


    se::Polygon& Entity::getHitbox()
    {
        this->hitbox.setPosition(this->sprite.getPosition());
        this->hitbox.setRotation(this->sprite.getRotation());
        this->hitbox.setScale(this->sprite.getScale());
        return this->hitbox;
    }


    se::Sprite& Entity::getSprite()
    {
        return this->sprite;
    }


    void Entity::hit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        for (unsigned int i = 0; i < this->modifiers.size(); ++i)
        {
            this->modifiers[i]->onHit(otherEntity, collisionGroup, projectionVector, projectionScalar);
        }
    }


    void Entity::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < this->modifiers.size(); ++i)
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