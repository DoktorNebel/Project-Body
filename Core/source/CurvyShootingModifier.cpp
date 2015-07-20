#include "CurvyShootingModifier.h"

#include "Spawner.h"
#include "ProjectileModifier.h"

namespace bc
{
    CurvyShootingModifier::CurvyShootingModifier(int level)
    {
        this->upgrade(level);
        this->fireRate = 0.01f;
        this->fireCounter = 0.0f;
        this->curvyfireRate = 0.05f;
        this->curvyfireCounter = 0.0f;
    }


    void CurvyShootingModifier::shoot(float elapsedTime)
    {
        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate)
        {
            this->fireCounter = 0.0f;

            std::vector<IModifier*> modifiers;
            float spreadDirection = (float)(rand() % 5 - 2) + 90.0f;
            se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
            directionVector *= 1500.0f;
            modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
        }

        this->curvyfireCounter += elapsedTime;
        if (this->curvyfireCounter >= this->curvyfireRate)
        {
            this->curvyfireCounter = 0.0f;

            for (unsigned int i = 0; i < this->movementPatterns.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ProjectileModifier(se::Vector2(0.0f, 0.0f), 2.0f));
                MovementPatternModifier* move = new MovementPatternModifier(this->movementPatterns[i], 0.0f, 1.0f, MovementPatternModifier::Style::Kill);
                //printf(move->noRotate ? "true" : "false");
                modifiers.push_back(move);
                Spawner::spawn(this->entity->getSprite().getPosition(), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }
    }


    void CurvyShootingModifier::setLevel()
    {
        switch (this->level)
        {
        case 2:
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_1"));
            break;
        }
    }
}