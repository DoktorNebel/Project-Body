#pragma once


namespace bc
{
    extern class Entity;

    class IModifier
    {
    public:

        Entity* entity;

    public:

        virtual void onCreate() = 0;
        virtual void onUpdate(float elapsedTime) = 0;
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup) = 0;
    };
}