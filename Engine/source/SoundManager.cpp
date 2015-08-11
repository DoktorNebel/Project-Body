#include "SoundManager.h"

#include "AL\al.h"
#include "AL\alc.h"

#include "Content.h"

namespace se
{
    void SoundManager::initialize()
    {
        ALCdevice* device = alcOpenDevice(0);
        if (device) 
        {
            ALCcontext* context = alcCreateContext(device, 0);
            if (context) 
            {
                alcMakeContextCurrent(context);
            }
            else
            {
                printf("Sound context creation failed. Sounds will be disabled");
                //TODO(maybe): disable sounds
            }
        }
        else
        {
            printf("No sound device found. Sounds will be disabled");
            //TODO(maybe): disable sounds
        }
        Content::loadSounds(this->buffers);
    }


    void SoundManager::update()
    {

    }


    void SoundManager::playSound(Sound& sound)
    {

    }
}