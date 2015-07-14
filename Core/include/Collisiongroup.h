#pragma once

namespace bc
{
    struct CollisionGroup
    {
        enum Type
        {
            Players,
            Enemies,
            ScrollingEnemies,
            PlayerProjectiles,
            EnemyProjectiles,
            Items,
            LevelElements,
            Particles
        };
    };
}