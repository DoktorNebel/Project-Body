#include "PlayerSatelliteModifier.h"

#include "Entity.h"
#include "MathFunctions.h"
#include "Input.h"
#include "Spawner.h"
#include "ProjectileModifier.h"
#include "InputActions.h"

namespace bc
{
    PlayerSatelliteModifier::PlayerSatelliteModifier(PlayerModifier* player)
        : player(player)
        , currentOrbitPosition(0.0f)
        , fireRate(0.01f)
        , fireCounter(0.0f)
        , lifeTime(20.0f)
    {

    }


    void PlayerSatelliteModifier::onCreate()
    {
        this->entity->getSprite().setScale(se::Vector2(0.5f, 0.5f));
    }


    void PlayerSatelliteModifier::onUpdate(float elapsedTime)
    {
        this->currentOrbitPosition += 500.0f * elapsedTime;
        if (this->currentOrbitPosition >= 360.0f)
            this->currentOrbitPosition = 0.0f;

        float orbitPosRad = this->currentOrbitPosition * 0.0174532925f;
        se::Vector2 offset(cos(orbitPosRad), sin(orbitPosRad));
        this->entity->getSprite().setPosition(this->player->entity->getSprite().getPosition() + offset * 50.0f);

        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate && se::Input::getActionValue(bg::InputAction::Shoot))
        {
            this->fireCounter = 0.0f;
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new ProjectileModifier(se::Vector2(rand() % 101 - 50, 1500), 2.0f));
            Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 9 - 4, 16), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
        }

        this->lifeTime -= elapsedTime;
        if (this->lifeTime <= 0.0f || this->player->entity->dead)
            this->entity->dead = true;
    }


    void PlayerSatelliteModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}