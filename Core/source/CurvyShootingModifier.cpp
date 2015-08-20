#include "CurvyShootingModifier.h"

#include "Spawner.h"
#include "ProjectileModifier.h"

namespace bc
{
    CurvyShootingModifier::CurvyShootingModifier(int level)
    {
        this->upgrade(level);
        this->fireRate = 0.02f;
        this->fireCounter = 0.0f;
        this->curvyfireRate = 0.01f;
        this->curvyfireCounter = 0.0f;
    }


    void CurvyShootingModifier::shoot(float elapsedTime)
    {
        this->fireCounter += elapsedTime;
        while (this->fireCounter >= this->fireRate)
        {
            this->fireCounter -= this->fireRate;
        
            std::vector<IModifier*> modifiers;
            float spreadDirection = 90.0f + (float)(rand() % 101 - 50) / 50.0f;
            se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
            directionVector *= 1500.0f;
            modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), "SchussKurvig", modifiers, CollisionGroup::PlayerProjectiles);
        }

        this->curvyfireCounter += elapsedTime;
        while (this->curvyfireCounter >= this->curvyfireRate)
        {
            this->curvyfireCounter -= this->curvyfireRate;

            for (unsigned int i = 0; i < this->movementPatterns.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ProjectileModifier(se::Vector2(0.0f, 0.0f), 2.0f, 1.0f / this->level));
                MovementPatternModifier* move = new MovementPatternModifier(this->movementPatterns[i], (float)(rand() % 101 - 50) / 50.0f, 0.5f, MovementPatternModifier::Style::Kill);
                modifiers.push_back(move);
                Spawner::spawn(this->entity->getSprite().getPosition(), "SchussKurvig", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }
    }


    void CurvyShootingModifier::setLevel()
    {
        this->movementPatterns.clear();
        switch (this->level)
        {
        case 2:
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_1"));
            break;

        case 3:
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_1"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_2"));
            break;

        case 4:
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_1"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_2"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_3"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_4"));
            break;

        case 5:
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_1"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_2"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_3"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_4"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_5"));
            this->movementPatterns.push_back(Spawner::getMovementPattern("CurvyShot_6"));
            break;
        }
    }
}