#include "MedicineBox.h"

#include "Input.h"
#include "InputActions.h"
#include "Spawner.h"
#include "PlayerSatelliteModifier.h"
#include "GameData.h"

namespace bc
{
    MedicineBox::MedicineBox(PlayerModifier* player)
        : player(player)
        , gamespeed(1.0f)
    {
        this->cooldowns[0] = 10.0f; //speed up
        this->cooldowns[1] = 10.0f; //speed down
        this->cooldowns[2] = 60.0f; //satellite
        memset(this->cooldownTimers, 0, 3 * sizeof(float));
    }


    void MedicineBox::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            if (this->cooldownTimers[i] > 0.0f)
                this->cooldownTimers[i] -= elapsedTime * (1.0f / this->gamespeed);
        }

        if (se::Input::actionPressed(bg::InputAction::Medicine1) && this->cooldownTimers[0] <= 0.0f && GameData::score >= 200)
        {
            this->cooldownTimers[0] = this->cooldowns[0];
            this->gamespeed *= 1.5f;
            GameData::score -= 200;
            GameData::multiplier *= 2.0f;
        }
        if (se::Input::actionPressed(bg::InputAction::Medicine2) && this->cooldownTimers[1] <= 0.0f && GameData::score >= 200)
        {
            this->cooldownTimers[1] = this->cooldowns[1];
            this->gamespeed *= 0.5f;
            GameData::score -= 200;
            GameData::multiplier *= 0.5f;
        }
        if (se::Input::actionPressed(bg::InputAction::Medicine3) && this->cooldownTimers[2] <= 0.0f && GameData::score >= 500)
        {
            this->cooldownTimers[2] = this->cooldowns[2];
            GameData::score -= 500;

            std::vector<IModifier*> modifiers;
            modifiers.push_back(new PlayerSatelliteModifier(this->player));
            Spawner::spawn(this->player->entity->getSprite().getPosition(), "TestPlayer", modifiers, CollisionGroup::Players);
        }
    }
}