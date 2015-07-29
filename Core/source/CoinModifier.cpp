#include "CoinModifier.h"

#include <algorithm>

#include "Spawner.h"
#include "MathFunctions.h"
#include "HomingMovementModifier.h"
#include "GameData.h"
#include "Engine.h"

namespace bc
{
    CoinModifier::CoinModifier(unsigned int score)
        : score(score)
        , timer(0.5f)
    {

    }


    void CoinModifier::onCreate()
    {
        //this->entity->getSprite().setColor(se::Vector4(1.0f, 1.0f, 1.0f, 0.3f));
        this->players = Spawner::getEntities(CollisionGroup::Players);
        this->player = false;

        float rotation = (float)(rand() % 18000) / 100.0f * 0.0174532925f;
        float speed = (float)(rand() % 1000000) / 80.0f;
        this->velocity = se::Vector2(cos(rotation), sin(rotation)) * speed;
    }


    void CoinModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().setRotation(0.0f);

        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
        }

        if (this->entity->getSprite().getPosition().y + this->entity->getSprite().getHeight() * 2.0f * this->entity->getSprite().getScale().y <
            se::Engine::getActiveCamera().getActualPosition().y * (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom() -
            (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom())
        {
            this->entity->health = 0.0f;
        }

        if (!this->player)
        {
            this->entity->getSprite().move(this->velocity * elapsedTime);

            this->velocity.x *= 1.0f - elapsedTime;
            this->velocity.y -= 1000.0f * elapsedTime;

            this->timer -= elapsedTime;
            if (this->timer <= 0.0f)
            {
                std::vector<Entity>::iterator iter = std::find_if(this->players->begin(), this->players->end(), [this](Entity& entity)
                {
                    return se::Math::Distance(this->entity->getSprite().getPosition(), entity.getSprite().getPosition()) < 200.0f;
                });

                if (iter != this->players->end())
                {
                    this->player = true;
                    std::vector<CollisionGroup::Type> groups;
                    groups.push_back(CollisionGroup::Players);
                    IModifier* movement = new HomingMovementModifier(groups, 700.0f, false, 1000.0f, 0.0f);
                    movement->entity = this->entity;
                    movement->onCreate();
                    this->entity->modifiers.insert(this->entity->modifiers.begin(), movement);
                }
            }
        }
    }


    void CoinModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::Players)
        {
            this->entity->dead = true;
            GameData::addScore(this->score);
        }
    }
}