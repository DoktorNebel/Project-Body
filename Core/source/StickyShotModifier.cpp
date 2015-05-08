#include "StickyShotModifier.h"

#include "Entity.h"
#include "MathFunctions.h"

namespace bc
{
    StickyShotModifier::StickyShotModifier(std::vector<std::vector<Entity>>* entities)
        : entities(entities)
        , radius(100.0f)
    {

    }


    StickyShotModifier::~StickyShotModifier()
    {

    }


    void StickyShotModifier::onCreate()
    {

    }


    void StickyShotModifier::onUpdate(float elapsedTime)
    {
        for (int i = 0; i < this->affectedEntities.size(); ++i)
        {
            this->affectedEntities[i]->sprite.setColor(se::Vector4(0.1f, 1.0f, 0.1f, 1.0f));
        }
    }


    void StickyShotModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        if (collisionGroup == CollisionGroup::Enemies)
        {
            for (int i = 0; i < this->entities[CollisionGroup::Enemies].size(); ++i)
            {
                if (se::Math::Distance((*this->entities)[CollisionGroup::Enemies][i].getSprite().getPosition(), otherEntity->getSprite().getPosition()) <= this->radius)
                {
                    this->affectedEntities.push_back(&(*this->entities)[CollisionGroup::Enemies][i]);
                }
            }
        }
    }
}