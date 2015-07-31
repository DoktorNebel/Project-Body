#include "LaserShootingModifier.h"

#include "Spawner.h"
#include "Input.h"
#include "InputActions.h"
#include "Engine.h"
#include "Camera.h"

namespace bc
{
    LaserShootingModifier::LaserShootingModifier(int level)
        : shooting(false)
    {
        this->upgrade(level);
    }


    void LaserShootingModifier::shoot(float elapsedTime)
    {
        if (!this->shooting)
        {
            this->shooting = true;
            this->lasers.clear();

            std::vector<IModifier*> modifiers;
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Bottom, 0, this, (float)this->level * 50.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[0], modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            modifiers.clear();
            LaserModifier* middleLaser = new LaserModifier(LaserModifier::LaserPart::Middle, 0, this, (float)this->level * 50.0f);
            modifiers.push_back(middleLaser);
            Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[1], modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            modifiers.clear();
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Top, middleLaser, this, (float)this->level * 50.0f));
            Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[2], modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            se::Engine::getActiveCamera().setPermanentScreenshake(0.2f * this->level);
        }
    }


    void LaserShootingModifier::setLevel()
    {
        switch (this->level)
        {
        case 2:
            this->spriteNames[0] = "Laser_Bottom_0";
            this->spriteNames[1] = "Laser_Middle_0";
            this->spriteNames[2] = "Laser_Top_0";
            break;

        case 3:
            this->spriteNames[0] = "Laser_Bottom_1";
            this->spriteNames[1] = "Laser_Middle_1";
            this->spriteNames[2] = "Laser_Top_1";
            break;

        case 4:
            this->spriteNames[0] = "Laser_Bottom_2";
            this->spriteNames[1] = "Laser_Middle_2";
            this->spriteNames[2] = "Laser_Top_2";
            break;

        case 5:
            this->spriteNames[0] = "Laser_Bottom_3";
            this->spriteNames[1] = "Laser_Middle_3";
            this->spriteNames[2] = "Laser_Top_3";
            break;
        }

        this->shooting = false;
    }


    void LaserShootingModifier::stopShooting()
    {
        this->shooting = false;
    }
}