#pragma once

#include <vector>

#include "Sound.h"

namespace se
{
    class SoundManager
    {
    private:

        std::vector<unsigned int> buffers;
        unsigned int sources[256];
        unsigned int nextSource;

    private:

        int findSourceId(Sound& sound);
        
    public:

        void initialize();
        void update();
        void playSound(Sound& sound);
        void pauseSound(Sound& sound);
        void resumeSound(Sound& sound);
        void stopSound(Sound& sound);
    };
}