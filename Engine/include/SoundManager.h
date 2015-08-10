#pragma once

#include <vector>

namespace se
{
    class SoundManager
    {
        static std::vector<unsigned int> buffers;
        static unsigned int sources[32];

    };
}