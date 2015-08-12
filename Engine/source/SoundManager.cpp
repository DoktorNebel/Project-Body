#include "SoundManager.h"

#include "AL\al.h"
#include "AL\alc.h"

#include "Content.h"

namespace se
{
    int SoundManager::findSourceId(Sound& sound)
    {
        for (unsigned int i = 0; i < this->nextSource; ++i)
        {
            int id;
            alGetSourcei(this->sources[i], AL_BUFFER, &id);
            if (id == sound.getSoundId())
                return (int)this->sources[i];
        }

        return -1;
    }


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
            }
        }
        else
        {
            printf("No sound device found. Sounds will be disabled");
        }
        Content::loadSounds(this->buffers);

        alGenSources(256, this->sources);
        
        this->nextSource = 0;
    }


    void SoundManager::update()
    {
        for (unsigned int i = 0; i < this->nextSource; ++i)
        {
            int state;
            alGetSourcei(this->sources[i], AL_SOURCE_STATE, &state);
            if (state == AL_STOPPED)
            {
                this->sources[i] = this->sources[this->nextSource - 1];
                --this->nextSource;
            }
        }
    }


    void SoundManager::playSound(Sound& sound)
    {
        if (this->nextSource < 256)
        {
            alSourcei(this->sources[this->nextSource], AL_BUFFER, this->buffers[sound.getSoundId()]);
            alSourcef(this->sources[this->nextSource], AL_GAIN, sound.getVolume());
            alSourcef(this->sources[this->nextSource], AL_PITCH, sound.getPitch());
            alSourcei(this->sources[this->nextSource], AL_LOOPING, (int)sound.getLooping());

            float angle = 90.0f - sound.getBalance() * 90.0f;
            angle *= 0.0174532925f;
            se::Vector3 sourcePos(cos(angle), 0.0f, sin(angle));
            alSourcefv(this->sources[this->nextSource], AL_POSITION, (ALfloat*)&sourcePos);

            alSourcePlay(this->sources[this->nextSource]);

            sound.setSourceId(this->sources[this->nextSource]);

            ++this->nextSource;
        }
    }


    void SoundManager::pauseSound(Sound& sound)
    {
        alSourcePause(sound.getSourceId());
    }


    void SoundManager::resumeSound(Sound& sound)
    {
        alSourcePlay(sound.getSourceId());
    }


    void SoundManager::stopSound(Sound& sound)
    {
        alSourceStop(sound.getSourceId());
        sound.setSourceId(0);
    }
}