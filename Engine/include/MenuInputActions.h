#pragma once

namespace se
{
    struct InputAction
    {
        enum Type
        {
            MenuLeft = 0,
            MenuRight,
            MenuUp,
            MenuDown,
            MenuConfirm,
            MenuBack
        };
    };
}