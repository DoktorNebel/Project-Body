#include "GooModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Spawner.h"
#include "GooParticleModifier.h"
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


    se::Vector2 GooModifier::getMidPoint()
    {
        return this->midPoint;
    }


    void GooModifier::onCreate()
    {
        for (int j = 0; j < 10; ++j)
        {
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new GooParticleModifier(this));
            Entity entity(se::Content::getSprite("Funke1"), modifiers);
            Spawner::spawn(this->midPoint + (this->entity->getSprite().getPosition() - this->midPoint) * j / 10 + se::Vector2(rand() % 6, rand() % 6), entity, CollisionGroup::Particles);
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