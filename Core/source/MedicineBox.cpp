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
    }
}