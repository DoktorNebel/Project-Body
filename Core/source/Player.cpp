#include "Player.h"

#include "Content.h"
#include "Input.h"
#include "InputActions.h"

namespace bc
{
    Player::Player()
        : maxHealth(100.0f)
        , health(100.0f)
        , speed(500.0f)
        , sprite(se::Content::getSprite("StaminaBar"))
    {
        this->sprite.setRotation(180.0f);
    }


    Player::~Player()
    {

    }


    se::Rectangle Player::getHitbox()
    {
        return this->sprite.getRect();
    }


    se::Sprite& Player::getSprite()
    {
        return this->sprite;
    }


    bool Player::isDead()
    {
        return this->health <= 0.0f;
    }


    void Player::hit(Player* otherEntity)
    {

    }


    void Player::hit(Projectile* otherEntity)
    {

    }


    void Player::hit(Enemy* otherEntity)
    {

    }


    void Player::hit(Item* otherEntity)
    {

    }


    void Player::hit(LevelElement* otherEntity)
    {

    }


    void Player::update(float elapsedTime)
    {
        float x = -this->speed * se::Input::getActionValue(bg::InputActions::Left) * elapsedTime + this->speed * se::Input::getActionValue(bg::InputActions::Right) * elapsedTime;
        float y = this->speed * se::Input::getActionValue(bg::InputActions::Up) * elapsedTime - this->speed * se::Input::getActionValue(bg::InputActions::Down) * elapsedTime;
        this->sprite.move(se::Vector2(x, y));
    }
}