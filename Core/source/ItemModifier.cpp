#include "ItemModifier.h"

#include "Entity.h"
#include "PlayerModifier.h"
#include "MathFunctions.h"
#include "GameData.h"

namespace bc
{
    ItemModifier::ItemModifier(Effect::Type effect)
        : effect(effect)
    {

    }


    void ItemModifier::onCreate()
    {
        this->entity->getSprite().setScale(se::Vector2(2.0f, 2.0f));
    }


    void ItemModifier::onUpdate(float elapsedTime)
    {
        this->entity->getSprite().move(se::Vector2(0.0f, -100.0f) * elapsedTime);
    }


    void ItemModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::Players && !this->entity->dead)
        {
            PlayerModifier* player = (PlayerModifier*)otherEntity->modifiers[0];
            float startRot;
            switch (this->effect)
            {
            case Effect::Spreadshot:
                player->shootingDirections.push_back(0.0f);
                startRot = player->shootingDirections.size() % 2 == 0 ? 5.0f - 10.0f * (float)(player->shootingDirections.size() / 2) : -10.0f * (float)(player->shootingDirections.size() / 2);
                for (unsigned int i = 0; i < player->shootingDirections.size(); ++i)
                {
                    player->shootingDirections[i] = startRot + (float)i * 10.0f + 90.0f;
                }
                break;

            case Effect::Backshot:
                player->backShootingDirections.push_back(0.0f);
                startRot = player->backShootingDirections.size() % 2 == 0 ? 5.0f - 10.0f * (float)(player->backShootingDirections.size() / 2) : -10.0f * (float)(player->backShootingDirections.size() / 2);
                startRot += 180.0f;
                for (unsigned int i = 0; i < player->backShootingDirections.size(); ++i)
                {
                    player->backShootingDirections[i] = startRot + (float)i * 10.0f + 90.0f;
                }
                break;

            case Effect::DoubleScore:
                GameData::multiplier *= 2.0f;
                break;
            }

            this->entity->dead = true;
        }
    }
}