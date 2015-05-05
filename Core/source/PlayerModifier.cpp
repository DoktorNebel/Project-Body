#include "PlayerModifier.h"

#include "Input.h"
#include "InputActions.h"
#include "Entity.h"
#include "Spawner.h"
#include "Content.h"
#include "ProjectileModifier.h"

namespace bc
{
    void PlayerModifier::onCreate()
    {
        this->speed = 500.0f;
        this->fireRate = 0.01f;
        this->fireCounter = 0.0f;
    }


    void PlayerModifier::onUpdate(float elapsedTime)
    {
        float x = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Right) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Left);
        float y = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Up) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Down);
        this->entity->getSprite().move(se::Vector2(x, y));

        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate && se::Input::getActionValue(bg::InputAction::Shoot))
        {
            this->fireCounter = 0.0f;
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new ProjectileModifier());
            Spawner::spawn(this->entity->getSprite().getPosition(), Entity(se::Content::getSprite("StaminaBar"), modifiers), CollisionGroup::PlayerProjectiles);
        }
    }


    void PlayerModifier::onHit(Entity* otherEntity)
    {

    }
}