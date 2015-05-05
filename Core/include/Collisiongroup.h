#pragma once

namespace bc
{
    struct CollisionGroup
    {
        enum Type
        {
            Players,
            Enemies,
            PlayerProjectiles,
            EnemyProjectiles,
            Items,
            LevelElements
        };
    };
}