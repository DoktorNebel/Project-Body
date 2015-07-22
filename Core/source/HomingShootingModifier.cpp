#include "HomingShootingModifier.h"

#include "ProjectileModifier.h"
#include "HomingMovementModifier.h"
#include "Spawner.h"

namespace bc
{
    HomingShootingModifier::HomingShootingModifier(int level)
    {
        this->upgrade(level);
        this->fireRate = 0.05f;
        this->fireCounter = 0.0f;
    }


    void HomingShootingModifier::shoot(float elapsedTime)
    {
        this->fireCounter += elapsedTime;
        while (this->fireCounter >= this->fireRate)
        {
            this->fireCounter -= this->fireRate;
            for (unsigned int i = 0; i < this->shootingDirections.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ProjectileModifier(se::Vector2(0.0f, 0.0f), 2.0f));
                std::vector<CollisionGroup::Type> groups;
                groups.push_back(CollisionGroup::Enemies);
                groups.push_back(CollisionGroup::ScrollingEnemies);
                modifiers.push_back(new HomingMovementModifier(groups, 1500.0f, false, 0.01f, this->shootingDirections[i]));
                Spawner::spawn(this->entity->getSprite().getPosition(), "PlayerProjectile", modifiers, CollisionGroup::PlayerProjectiles);
            }
        }
    }


    void HomingShootingModifier::setLevel()
    {
        this->shootingDirections.clear();
        switch (this->level)
        {
        case 2:
            this->shootingDirections.push_back(90.0f);
            break;

        case 3:
            this->shootingDirections.push_back(-30.0f + 90.0f);
            this->shootingDirections.push_back(30.0f + 90.0f);
            break;

        case 4:
            this->shootingDirections.push_back(-45.0f + 90.0f);
            this->shootingDirections.push_back(90.0f);
            this->shootingDirections.push_back(45.0f + 90.0f);
            break;

        case 5:
            this->shootingDirections.push_back(-60.0f + 90.0f);
            this->shootingDirections.push_back(-20.0f + 90.0f);
            this->shootingDirections.push_back(20.0f + 90.0f);
            this->shootingDirections.push_back(60.0f + 90.0f);
            break;
        }
    }
}