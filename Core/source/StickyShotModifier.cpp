#include "StickyShotModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "GooModifier.h"
#include "ParticleModifier.h"
#include "Spawner.h"
#include "Content.h"

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
        this->entity->getSprite().setScale(se::Vector2(3.0f, 3.0f));
        this->entity->getSprite().setColor(se::Vector4(0.1f, 1.0f, 0.1f, 1.0f));
    }


    void StickyShotModifier::onUpdate(float elapsedTime)
    {

    }


    void StickyShotModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        if (collisionGroup == CollisionGroup::Enemies)
        {
            std::vector<Entity*> affectedEntities;
            se::Vector2 midPoint(0.0f, 0.0f);
            for (int i = 0; i < (*this->entities)[CollisionGroup::Enemies].size(); ++i)
            {
                if (se::Math::Distance((*this->entities)[CollisionGroup::Enemies][i].getSprite().getPosition(), otherEntity->getSprite().getPosition()) <= this->radius)
                {
                    midPoint += (*this->entities)[CollisionGroup::Enemies][i].getSprite().getPosition();
                    affectedEntities.push_back(&(*this->entities)[CollisionGroup::Enemies][i]);
                }
            }

            midPoint /= affectedEntities.size();

            for (int i = 0; i < affectedEntities.size(); ++i)
            {
                std::vector<Entity*> otherEntities = affectedEntities;
                otherEntities.erase(std::find(otherEntities.begin(), otherEntities.end(), affectedEntities[i]));
                GooModifier* modifier = new GooModifier(otherEntities, midPoint);
                modifier->onCreate();
                affectedEntities[i]->modifiers.push_back(modifier);
            }

            for (int i = 0; i < 50; ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ParticleModifier(se::Vector2(rand() % 2001 - 1000, rand() % 2001 - 1000), rand() % 501 / 1000.0f));
                se::Sprite sprite = se::Content::getSprite("Funke1");
                sprite.setColor(se::Vector4(0.1f, 1.0f, 0.1f, 1.0f));
                Spawner::spawn(this->entity->getSprite().getPosition(), Entity(sprite, modifiers), CollisionGroup::Particles);
            }
        }
    }
}