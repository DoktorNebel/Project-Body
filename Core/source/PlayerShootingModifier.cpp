#include "PlayerShootingModifier.h"

#include "Input.h"
#include "InputActions.h"
#include "Spawner.h"
#include "AnimatedSprite.h"
#include "AnimationModifier.h"
#include "ProjectileModifier.h"
#include "StickyShotModifier.h"
#include "AnimationModifier.h"
#include "Content.h"
#include "MathFunctions.h"
#include "MenuData.h"
#include "Engine.h"

namespace bc
{
    void PlayerShootingModifier::onCreate()
    {
        this->stickyFireRate = 1.0f;
    }


    void PlayerShootingModifier::onUpdate(float elapsedTime)
    {
        if (se::Input::getActionValue(bg::InputAction::Shoot))
            this->shoot(elapsedTime);

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

        ((bg::MenuData*)se::Engine::getMenu()->data)->stickyShotCooldown = se::Math::Clamp(0.0f, 1.0f, this->stickyFireCounter / this->stickyFireRate);
    }


    void PlayerShootingModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }


    void PlayerShootingModifier::upgrade(int level)
    {
        if (level == 0)
            this->level += this->level < 5;
        else
            this->level = level;

        this->setLevel();
    }


    void PlayerShootingModifier::setEntities(std::vector<std::vector<Entity>>* entities)
    {
        this->entities = entities;
    }


    int PlayerShootingModifier::getLevel()
    {
        return this->level;
    }
}