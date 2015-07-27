#include "LaserShootingModifier.h"

#include "Spawner.h"
#include "Input.h"
#include "InputActions.h"

namespace bc
{
    LaserShootingModifier::LaserShootingModifier()
    {

    }


    void LaserShootingModifier::shoot(float elapsedTime)
    {
        if (se::Input::actionPressed(bg::InputAction::Shoot))
        {
            this->lasers.clear();

            std::vector<IModifier*> modifiers;
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Bottom));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Laser_Bottom", modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            modifiers.clear();
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Middle));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Laser_Middle", modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());

            modifiers.clear();
            modifiers.push_back(new LaserModifier(LaserModifier::LaserPart::Top));
            Spawner::spawn(this->entity->getSprite().getPosition(), "Laser_Top", modifiers, CollisionGroup::PlayerProjectiles);
            this->lasers.push_back((LaserModifier*)modifiers.back());
        }
    }


    void LaserShootingModifier::setLevel()
    {

    }
}