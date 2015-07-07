#pragma once

namespace be
{
    struct InputActions
    {
        enum Type
        {
            CameraLeft = 17,
            CameraRight,
            CameraUp,
            CameraDown,
            DeleteTile
        };
    };
}