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
        this->sprite.addAnimation("Idle");
        this->sprite.addSprite("Idle", se::Content::getSprite("s_heroA"));

        this->sprite.addAnimation("Strafe");
        this->sprite.setSpeed("Strafe", 0.02f);
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroA"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroB"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroC"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroD"));

        this->sprite.addAnimation("Strafe_Reverse");
        this->sprite.setSpeed("Strafe_Reverse", 0.02f);
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroD"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroC"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroB"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroA"));

        this->sprite.addAnimation("Idle_Strafing");
        this->sprite.addSprite("Idle_Strafing", se::Content::getSprite("s_heroD"));
    }


    void PlayerModifier::onUpdate(float elapsedTime)
    {
        float x = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Right) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Left);
        float y = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Up) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Down);
        this->sprite.move(se::Vector2(x, y));
        if (this->sprite.getPosition().y - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 < -(int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom())
            this->sprite.setPosition(se::Vector2(this->sprite.getPosition().x, -(int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom() + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));
        if (this->sprite.getPosition().y + this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2 > (int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom())
            this->sprite.setPosition(se::Vector2(this->sprite.getPosition().x, (int)se::Engine::getSettings().renderResolutionHeight / 2 * se::Engine::getActiveCamera().getZoom() - this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y / 2));

        int strafing = se::Input::actionReleased(bg::InputAction::Right) - se::Input::actionReleased(bg::InputAction::Left);
        if (strafing != 0)
        {
            if (this->sprite.getCurrentAnimation() == "Idle_Strafing")
            {
                this->sprite.setScale(se::Vector2(strafing, 1));
                this->sprite.changeAnimation("Strafe_Reverse");
            }
            else if (this->sprite.getCurrentAnimation() == "Strafe")
            {
                this->sprite.changeAnimation("Idle");
                this->sprite.setScale(se::Vector2(1.0f, 1.0f));
            }
        }

        strafing = (int)se::Input::getActionValue(bg::InputAction::Right) - (int)se::Input::getActionValue(bg::InputAction::Left);
        if (strafing != 0 && this->sprite.getCurrentAnimation() == "Idle")
        {
            this->sprite.setScale(se::Vector2(strafing, 1));
            this->sprite.changeAnimation("Strafe");
        }

        if (this->sprite.getCurrentAnimation() == "Strafe" && this->sprite.finishedAnimation())
        {
            this->sprite.changeAnimation("Idle_Strafing");
        }

        if (this->sprite.getCurrentAnimation() == "Strafe_Reverse" && this->sprite.finishedAnimation())
        {
            this->sprite.changeAnimation("Idle");
            this->sprite.setScale(se::Vector2(1.0f, 1.0f));
        }

        this->sprite.update(elapsedTime);

        this->entity->sprite = this->sprite.getCurrentSprite();

        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
        }
    }


    void PlayerModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (collisionGroup == CollisionGroup::LevelElements)
            this->sprite.move(projectionVector * projectionScalar);// *(this->sprite.getPosition().x < otherEntity->getSprite().getPosition().x ? -1.0f : 1.0f));
        otherEntity->health -= this->entity->maxHealth;
    }
}