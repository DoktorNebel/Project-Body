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
        this->speed = 400.0f;
        this->sprite.addAnimation("Idle");
        this->sprite.addSprite("Idle", se::Content::getSprite("s_heroA"));

        this->sprite.addAnimation("Strafe");
        this->sprite.setSpeed("Strafe", 0.05f);
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroA"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroB"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroC"));
        this->sprite.addSprite("Strafe", se::Content::getSprite("s_heroD"));

        this->sprite.addAnimation("Strafe_Reverse");
        this->sprite.setSpeed("Strafe_Reverse", 0.05f);
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroD"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroC"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroB"));
        this->sprite.addSprite("Strafe_Reverse", se::Content::getSprite("s_heroA"));

        this->sprite.addAnimation("Idle_Strafing");
        this->sprite.addSprite("Idle_Strafing", se::Content::getSprite("s_heroD"));

        std::vector<se::Vector2> points;
        points.push_back(se::Vector2(-1.0f, 1.0f));
        points.push_back(se::Vector2(-1.0f, -1.0f));
        points.push_back(se::Vector2(1.0f, -1.0f));
        points.push_back(se::Vector2(1.0f, 1.0f));
        this->entity->hitbox = se::Polygon(points);
    }


    void PlayerModifier::onUpdate(float elapsedTime)
    {
        float x = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Right) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Left);
        float y = this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Up) - this->speed * elapsedTime * se::Input::getActionValue(bg::InputAction::Down);
        this->lastMove = se::Vector2(x, y);
        this->sprite.move(this->lastMove);

        se::Rectangle screenRect(se::Engine::getActiveCamera().getActualPosition().y * (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom() + (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom() - this->entity->sprite.getHeight(),
            se::Engine::getActiveCamera().getActualPosition().y * (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom() - (float)se::Engine::getSettings().renderResolutionHeight / 2.0f * se::Engine::getActiveCamera().getZoom() + this->entity->sprite.getHeight(),
            se::Engine::getActiveCamera().getActualPosition().x * (float)se::Engine::getSettings().renderResolutionWidth / 2.0f * se::Engine::getActiveCamera().getZoom() - (float)se::Engine::getSettings().renderResolutionWidth / 2.0f * se::Engine::getActiveCamera().getZoom() + this->entity->sprite.getWidth(),
            se::Engine::getActiveCamera().getActualPosition().x * (float)se::Engine::getSettings().renderResolutionWidth / 2.0f * se::Engine::getActiveCamera().getZoom() + (float)se::Engine::getSettings().renderResolutionWidth / 2.0f * se::Engine::getActiveCamera().getZoom() - this->entity->sprite.getWidth());

        se::Rectangle playerRect = this->sprite.getCurrentSprite().getRect();

        while (!screenRect.overlap(playerRect) && (this->entity->getSprite().getPosition().y > 0.0f || (this->entity->getSprite().getPosition().y < 0.0f && this->lastMove.y <= 0.0f)))
        {
            this->sprite.move(se::Vector2((playerRect.right <= screenRect.left) * 0.5f - (playerRect.left >= screenRect.right) * 0.5f, (playerRect.top <= screenRect.bottom) * 0.5f - (playerRect.bottom >= screenRect.top) * 0.5f));
            playerRect = this->sprite.getCurrentSprite().getRect();
        }

        if (playerRect.bottom + this->entity->sprite.getHeight() * this->entity->getSprite().getScale().y * 2.0f < screenRect.bottom)
            this->entity->health = 0.0f;

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
        {
            if (this->lastMove == se::Vector2())
            {
                this->sprite.move(projectionVector * projectionScalar * -3.0f);
            }
            else
            {
                this->sprite.move(this->lastMove * -1.5f);
            }
        }
        else
        {
            otherEntity->health -= this->entity->maxHealth;
        }
    }
}