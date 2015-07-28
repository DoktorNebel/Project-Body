#include "LaserShootingModifier.h"

#include "Spawner.h"
#include "Input.h"
#include "InputActions.h"
#include "Engine.h"
#include "Camera.h"

namespace bc
{
    LaserShootingModifier::LaserShootingModifier(PlayerShootingModifier* previousShot)
        : previousShot(previousShot)
        , timer(10.0f)
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

            se::Engine::getActiveCamera().setPermanentScreenshake(1.0f);
        }

        this->timer -= elapsedTime;
        if (this->timer <= 0.0f)
        {
            for (unsigned int i = 0; i < this->lasers.size(); ++i)
            {
                this->lasers[i]->entity->health = 0.0f;
            }
            this->entity->modifiers.push_back(this->previousShot);
            std::vector<IModifier*>::iterator iter = std::find(this->entity->modifiers.begin(), this->entity->modifiers.end(), this);
            this->entity->modifiers.erase(iter);
            delete this;
        }
    }


    void LaserShootingModifier::setLevel()
    {

    }
}