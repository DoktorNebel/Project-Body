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
    PlayerModifier::PlayerModifier(std::vector<std::vector<Entity>>* entities)
        : entities(entities)
    {

    }


    PlayerModifier::~PlayerModifier()
    {

    }


    void PlayerModifier::onCreate()
    {
        this->speed = 500.0f;
        this->fireRate = 0.01f;
		this->fireCounter = 0.0f;
		this->stickyFireRate = 1.0f;
		this->stickyFireCounter = 0.0f;
        this->entity->getSprite().setScale(se::Vector2(1.0f, 1.0f));
        this->shootingDirections.push_back(0.0f + 90.0f);
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

        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate && se::Input::getActionValue(bg::InputAction::Shoot))
        {
            this->fireCounter = 0.0f;

            for (unsigned int i = 0; i < this->shootingDirections.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                float spreadDirection = this->shootingDirections[i] + (float)(rand() % 11 - 5);
                se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
                directionVector *= 1500.0f;
                modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
                Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 9 - 4, 16), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }

            for (unsigned int i = 0; i < this->backShootingDirections.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                float spreadDirection = this->backShootingDirections[i] + (float)(rand() % 11 - 5);
                se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
                directionVector *= 1500.0f;
                modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
                Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 9 - 4, -16), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }

		this->stickyFireCounter += elapsedTime;
		if (this->stickyFireCounter >= this->stickyFireRate && se::Input::getActionValue(bg::InputAction::StickyShot))
		{
			this->stickyFireCounter = 0.0f;

            std::vector<IModifier*> modifiers;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.1f);
            sprite.addSprite("Idle", se::Content::getSprite("KlebSchuss1"));
            sprite.addSprite("Idle", se::Content::getSprite("KlebSchuss2"));
            sprite.addSprite("Idle", se::Content::getSprite("KlebSchuss3"));
            sprite.addSprite("Idle", se::Content::getSprite("KlebSchuss4"));
            modifiers.push_back(new AnimationModifier(sprite));
            modifiers.push_back(new ProjectileModifier(se::Vector2(rand() % 21 - 10, 200), 2.0f));
            modifiers.push_back(new StickyShotModifier(this->entities));
            Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(rand() % 9 - 4, 16), "KlebSchuss1", modifiers, CollisionGroup::PlayerProjectiles);
        }

        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
        }
    }


    void PlayerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::LevelElements)
            this->entity->getSprite().move(projectionVector * projectionScalar * (this->entity->getSprite().getPosition().x < otherEntity->getSprite().getPosition().x ? -1.0f : 1.0f));
        otherEntity->health -= this->entity->maxHealth;
    }
}