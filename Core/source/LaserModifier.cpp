#include "LaserModifier.h"

#include "Entity.h"
#include "Input.h"
#include "InputActions.h"
#include "Spawner.h"
#include "MathFunctions.h"
#include "Engine.h"

namespace bc
{
    LaserModifier::LaserModifier(LaserPart::Type part)
        : part(part)
    {
        this->speed = 100.0f;
        this->player = 0;
    }


    void LaserModifier::onCreate()
    {
        if (this->part == LaserPart::Top)
        {
            this->entity->getSprite().move(se::Vector2(0.0f, 64.0f));
        }

        std::vector<Entity>* players = Spawner::getEntities(CollisionGroup::Players);
        std::vector<Entity>::iterator iter = std::_Min_element(players->begin(), players->end(), [this](Entity& left, Entity& right)
        {
            return se::Math::Distance(left.getSprite().getPosition(), this->entity->getSprite().getPosition()) < se::Math::Distance(right.getSprite().getPosition(), this->entity->getSprite().getPosition());
        });
        if (iter != players->end())
            this->player = (PlayerModifier*)iter->modifiers[0];

        this->lastPlayerPos = this->player->entity->getSprite().getPosition();
    }


    void LaserModifier::onUpdate(float elapsedTime)
    {
        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
            se::Engine::getActiveCamera().setPermanentScreenshake(0.0f);
        }

        if (this->part == LaserPart::Middle)
        {
            if (this->entity->getSprite().getScale().y < 10.0f)
                this->entity->getSprite().setScale(se::Vector2(1.0f, this->entity->getSprite().getScale().y + this->speed * elapsedTime));
            this->entity->getSprite().setPosition(this->player->entity->getSprite().getPosition() + se::Vector2(0.0f, this->entity->getSprite().getHeight() * this->entity->getSprite().getScale().y * 0.5f + 32.0f));
        }
        else if (this->part == LaserPart::Top)
        {
            this->entity->getSprite().setPosition(se::Vector2(this->player->entity->getSprite().getPosition().x, this->entity->getSprite().getPosition().y + this->speed * 33.0f * elapsedTime));
            this->entity->getSprite().move(this->player->entity->getSprite().getPosition() - this->lastPlayerPos);
        }
        else
        {
            this->entity->getSprite().setPosition(this->player->entity->getSprite().getPosition() + se::Vector2(0.0f, 16.0f));
        }

        if (se::Input::actionReleased(bg::InputAction::Shoot) || this->player->entity->health <= 0.0f)
        {
            this->entity->health = 0.0f;
        }

        this->lastPlayerPos = this->player->entity->getSprite().getPosition();
        this->elapsedTime = elapsedTime;
    }


    void LaserModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {
        if (se::Input::getActionValue(bg::InputAction::Shoot))
            this->entity->health = 1000000.0f;

        if (collisionGroup == CollisionGroup::Enemies || collisionGroup == CollisionGroup::ScrollingEnemies)
            otherEntity->health -= 500.0f * this->elapsedTime;
    }
}