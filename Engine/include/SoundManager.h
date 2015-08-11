#pragma once

#include <vector>

#include "Sound.h"

namespace se
{
    class SoundManager
    {
    private:

        std::vector<unsigned int> buffers;
        unsigned int sources[32];
        
    public:

        void initialize();
        void update();
        void playSound(Sound& sound);
    };
}