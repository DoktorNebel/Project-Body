#include "GooModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Spawner.h"
#include "ParticleModifier.h"
#include "Content.h"

namespace bc
{
    GooModifier::GooModifier(std::vector<Entity*> otherEntities, se::Vector2 midPoint)
        : otherEntities(otherEntities)
        , hitMarkerTime(0.005f)
        , timer(0.0f)
        , midPoint(midPoint)
    {

    }


    GooModifier::~GooModifier()
    {

    }


    void GooModifier::onCreate()
    {
        for (int i = 0; i < this->otherEntities.size(); ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ParticleModifier(se::Vector2(0.0f, 0.0f), 100.0f));
                Entity entity(se::Content::getSprite("Funke1"), modifiers);
                entity.getSprite().setColor(se::Vector4(0.1f, 1.0f, 0.1f, 1.0f));
                entity.getSprite().setScale(se::Vector2(5.0f, 5.0f));
                Spawner::spawn(this->midPoint + (this->otherEntities[i]->getSprite().getPosition() - this->midPoint) * j / 10, entity, CollisionGroup::Particles);
            }
        }
    }


    void GooModifier::onUpdate(float elapsedTime)
    {
        se::Vector4 color(0.1f, 1.0f, 0.1f, 1.0f);

        this->timer += elapsedTime;
        if (this->timer < this->hitMarkerTime)
        {
            color = se::Vector4(3.0f, 3.0f, 3.0f, 1.0f);
        }

        if (!this->entity->dead)
            this->entity->getSprite().setColor(color);

        se::Vector2 newMidpoint(0.0f, 0.0f);
        std::vector<Entity*>::iterator iter = this->otherEntities.begin();
        while (iter != this->otherEntities.end())
        {
            if ((*iter)->dead)
            {
                iter = this->otherEntities.erase(iter);
            }
            else
            {
                se::Vector2 movement = (this->midPoint - (*iter)->getSprite().getPosition()) * 0.05f * elapsedTime;
                (*iter)->getSprite().move(movement);
                newMidpoint += (*iter)->getSprite().getPosition();
                (*iter)->getSprite().setColor(color);
                ++iter;
            }
        }

        newMidpoint /= otherEntities.size();
        this->midPoint = newMidpoint;
    }


    void GooModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        this->timer = 0.0f;
        if (collisionGroup == CollisionGroup::PlayerProjectiles)
        {
            for (int i = 0; i < this->otherEntities.size(); ++i)
            {
                if (otherEntities[i]->health > 0.0f)
                {
                    this->otherEntities[i]->hit(otherEntity, CollisionGroup::Players);
                    this->otherEntities[i]->health -= otherEntity->damage;
                }
            }
        }
    }
}