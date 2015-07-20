#include "PlayerModifier.h"

#include "Input.h"
#include "InputActions.h"
#include "Entity.h"
#include "Spawner.h"
#include "Content.h"
#include "ProjectileModifier.h"
#include "MathFunctions.h"
#include "Engine.h"
#include "StickyShotModifier.h"
#include "AnimationModifier.h"

namespace bc
{
    PlayerModifier::PlayerModifier()
    {

    }


    PlayerModifier::~PlayerModifier()
    {

    }


    void PlayerModifier::onCreate()
    {
        this->speed = 500.0f;
        this->entity->getSprite().setScale(se::Vector2(1.0f, 1.0f));
    }


    void PlayerModifier::onUpdate(float elapsedTime)
    {
        float x = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Right) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Left);
        float y = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Up) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Down);
        this->entity->getSprite().move(se::Vector2(x, y));
		if (this->entity->getSprite().getPosition().y - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 < -(int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom())
			this->entity->getSprite().setPosition(se::Vector2(this->entity->getSprite().getPosition().x, -(int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom() + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));
		if (this->entity->getSprite().getPosition().y + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 > (int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom())
			this->entity->getSprite().setPosition(se::Vector2(this->entity->getSprite().getPosition().x, (int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom() - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));

        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
        }
    }


    void PlayerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::LevelElements)
            this->entity->getSprite().move(projectionVector * projectionScalar);// *(this->entity->getSprite().getPosition().x < otherEntity->getSprite().getPosition().x ? -1.0f : 1.0f));
        otherEntity->health -= this->entity->maxHealth;
    }
}