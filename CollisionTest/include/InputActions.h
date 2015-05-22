#pragma once

namespace test
{
    struct InputAction
    {
        enum Type
        {
            Left,
            Right,
            Up,
            Down,
            RotateLeft,
            RotateRight,
            ScaleUp,
            ScaleDown,
        };
    };
}