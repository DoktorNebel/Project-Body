#include "NormalShootingModifier.h"

#include "ProjectileModifier.h"
#include "Spawner.h"
#include "MathFunctions.h"

namespace bc
{
    NormalShootingModifier::NormalShootingModifier(int level)
    {
        this->upgrade(level);
        this->fireRate = 0.01f;
        this->fireCounter = 0.0f;
    }


    void NormalShootingModifier::shoot(float elapsedTime)
    {
        this->fireCounter += elapsedTime;
        while (this->fireCounter >= this->fireRate)
        {
            this->fireCounter -= this->fireRate;

            for (unsigned int i = 0; i < this->shootingOffsets.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                float spreadDirection = (float)(rand() % 11 - 5) + 90.0f;
                se::Vector2 directionVector(cos(spreadDirection * 0.0174532925f), sin(spreadDirection * 0.0174532925f));
                directionVector *= 1500.0f;
                modifiers.push_back(new ProjectileModifier(directionVector, 2.0f));
                Spawner::spawn(this->entity->getSprite().getPosition() + this->shootingOffsets[i], "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }
    }


    void NormalShootingModifier::setLevel()
    {
        this->shootingOffsets.clear();
        switch (this->level)
        {
        case 1:
            this->shootingOffsets.push_back(se::Vector2(0.0f, 10.0f));
            break;

        case 2:
            this->shootingOffsets.push_back(se::Vector2(-10.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(10.0f, 10.0f));
            break;

        case 3:
            this->shootingOffsets.push_back(se::Vector2(-15.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(0.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(15.0f, 10.0f));
            break;

        case 4:
            this->shootingOffsets.push_back(se::Vector2(-20.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(-5.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(5.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(20.0f, 10.0f));
            break;

        case 5:
            this->shootingOffsets.push_back(se::Vector2(-20.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(-5.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(5.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(20.0f, 10.0f));
            this->shootingOffsets.push_back(se::Vector2(-10.0f, 20.0f));
            this->shootingOffsets.push_back(se::Vector2(10.0f, 20.0f));
            break;
        }
    }
}