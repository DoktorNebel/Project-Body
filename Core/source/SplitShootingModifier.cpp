#include "SplitShootingModifier.h"

#include "Spawner.h"
#include "ProjectileModifier.h"
#include "MathFunctions.h"

namespace bc
{
    SplitShootingModifier::SplitShootingModifier(int level)
    {
        this->upgrade(level);
        this->fireRate = 0.01f;
        this->fireCounter = 0.0f;
    }


    void SplitShootingModifier::shoot(float elapsedTime)
    {
        this->fireCounter += elapsedTime;
        if (this->fireCounter >= this->fireRate)
        {
            this->fireCounter = 0.0f;

            for (unsigned int i = 0; i < this->shootingDirections.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                float spreadDirection = (float)(rand() % 11 - 5) + this->shootingDirections[i];
                se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
                directionVector *= 1500.0f;
                modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
                Spawner::spawn(this->entity->getSprite().getPosition() + se::Vector2(0.0f, 10.0f), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }
    }


    void SplitShootingModifier::setLevel()
    {
        this->shootingDirections.clear();
        float dif = 360.0f / this->level;
        for (int i = 0; i < this->level; ++i)
        {
            this->shootingDirections.push_back(90.0f + i * dif);
        }
    }
}