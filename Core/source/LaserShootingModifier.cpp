#include "LaserShootingModifier.h"

#include "Spawner.h"
#include "Input.h"
#include "InputActions.h"
#include "Engine.h"
#include "Camera.h"
#include "AnimatedSprite.h"
#include "AnimationModifier.h"

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
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Bottom, 0, this, (1.0f + (float)this->level * 0.5f) * 50.0f));
            se::AnimatedSprite start;
            start.addAnimation("Idle");
            start.setSpeed("Idle", 0.1f);
            start.addSprite("Idle", se::Content::getSprite("LazorStart1"));
            start.addSprite("Idle", se::Content::getSprite("LazorStart2"));
            start.addSprite("Idle", se::Content::getSprite("LazorStart3"));
            start.addSprite("Idle", se::Content::getSprite("LazorStart4"));
            start.addSprite("Idle", se::Content::getSprite("LazorStart5"));
            modifiers.push_back(new AnimationModifier(start));
            Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[0], modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            modifiers.clear();
            LaserModifier* middleLaser = new LaserModifier(LaserModifier::LaserPart::Middle, 0, this, (1.0f + (float)this->level * 0.5f) * 50.0f);
            modifiers.push_back(middleLaser);
            se::AnimatedSprite middle;
            middle.addAnimation("Idle");
            middle.setSpeed("Idle", 0.1f);
            middle.addSprite("Idle", se::Content::getSprite("LazorStrahl1"));
            middle.addSprite("Idle", se::Content::getSprite("LazorStrahl2"));
            modifiers.push_back(new AnimationModifier(middle));
            Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[1], modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            //modifiers.clear();
            //modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Top, middleLaser, this, ((float)this->level * 1.1f) * 50.0f));
            //se::AnimatedSprite end;
            //end.addAnimation("Idle");
            //end.setSpeed("Idle", 0.1f);
            //end.addSprite("Idle", se::Content::getSprite("LazorTreffer1"));
            //end.addSprite("Idle", se::Content::getSprite("LazorTreffer2"));
            //end.addSprite("Idle", se::Content::getSprite("LazorTreffer3"));
            //modifiers.push_back(new AnimationModifier(end));
            //Spawner::spawn(this->entity->getSprite().getPosition(), this->spriteNames[2], modifiers, CollisionGroup::PlayerProjectiles);
            //this->lasers.push_back((LaserModifier*)modifiers.back());

            se::Engine::getActiveCamera().setPermanentScreenshake(0.2f * this->level);
        }
    }


    void LaserShootingModifier::setLevel()
    {
        switch (this->level)
        {
        case 1:
            this->spriteNames[0] = "Laser_Bottom_0";
            this->spriteNames[1] = "Laser_Middle_0";
            this->spriteNames[2] = "Laser_Top_0";
            break;

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