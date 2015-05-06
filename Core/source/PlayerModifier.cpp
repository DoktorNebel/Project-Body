#include "PlayerModifier.h"

#include "Input.h"
#include "InputActions.h"
#include "Entity.h"
#include "Spawner.h"
#include "Content.h"
#include "ProjectileModifier.h"
#include "MathFunctions.h"
#include "Engine.h"

namespace bc
{
    void PlayerModifier::onCreate()
    {
        this->speed = 500.0f;
        this->fireRate = 0.005f;
        this->fireCounter = 0.0f;
        this->entity->getSprite().setScale(se::Vector2(0.4f, 0.5f));
    }


    void PlayerModifier::onUpdate(float elapsedTime)
    {
        float x = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Right) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Left);
        float y = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Up) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Down);
        this->entity->getSprite().move(se::Vector2(x, y));
        if (this->entity->getSprite().getPosition().x - this->entity->getSprite().getWidth() * this->entity->getSprite().getScale().x / 2 < -(int)se::Engine::getSettings().resolutionWidth / 2)
            this->entity->getSprite().setPosition(se::Vector2(-(int)se::Engine::getSettings().resolutionWidth / 2 + this->entity->getSprite().getWidth() * this->entity->getSprite().getScale().x / 2, this->entity->getSprite().getPosition().y));
        if (this->entity->getSprite().getPosition().x + this->entity->getSprite().getWidth() * this->entity->getSprite().getScale().x / 2 > (int)se::Engine::getSettings().resolutionWidth / 2)
            this->entity->getSprite().setPosition(se::Vector2((int)se::Engine::getSettings().resolutionWidth / 2 - this->entity->getSprite().getWidth() * this->entity->getSprite().getScale().x / 2, this->entity->getSprite().getPosition().y));
        if (this->entity->getSprite().getPosition().y - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 < -(int)se::Engine::getSettings().resolutionHeight / 2)
            this->entity->getSprite().setPosition(se::Vector2(this->entity->getSprite().getPosition().x, -(int)se::Engine::getSettings().resolutionHeight / 2 + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));
        if (this->entity->getSprite().getPosition().y + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 > (int)se::Engine::getSettings().resolutionHeight / 2)
            this->entity->getSprite().setPosition(se::Vector2(this->entity->getSprite().getPosition().x, (int)se::Engine::getSettings().resolutionHeight / 2 - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));

        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate && se::Input::getActionValue(bg::InputAction::Shoot))
        {
            this->fireCounter = 0.0f;
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new ProjectileModifier(se::Vector2(rand() % 151 - 75, 3000.0f), 0.3f));
            Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 9 - 4, 16.0f), Entity(se::Content::getSprite("PlayerProjectile"), modifiers), CollisionGroup::PlayerProjectiles);
        }
    }


    void PlayerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
    {
        otherEntity->health -= this->entity->maxHealth;
    }
}