#include "HitMarkerModifier.h"

#include "Entity.h"

namespace bc
{
    void HitMarkerModifier::onCreate()
    {
        this->hitMarkerTime = 0.005f;
        this->timer = 0.0f;
    }


    void HitMarkerModifier::onUpdate(float elapsedTime)
    {
        this->timer += elapsedTime;
        if (this->timer < this->hitMarkerTime)
            this->entity->getSprite().setColor(se::Vector4(3.0f, 3.0f, 3.0f, 1.0f));
        else
            this->entity->getSprite().setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void HitMarkerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup != CollisionGroup::LevelElements)
            this->timer = 0.0f;
    }
}