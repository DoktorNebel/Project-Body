#include "Sound.h"

#include <cassert>

namespace se
{
    Sound::Sound(unsigned int soundId)
        : looping(false)
        , volume(1.0f)
        , balance(0.0f)
        , pitch(1.0f)
        , soundId(soundId)
        , sourceId(0)
    {

    }


    bool Sound::getLooping()
    {
        return this->looping;
    }


    void Sound::setLooping(bool value)
    {
        this->looping = value;
    }


    float Sound::getVolume()
    {
        return this->volume;
    }


    void Sound::setVolume(float value)
    {
        assert(value >= 0.0f && value <= 1.0f);
        this->volume = value;
    }


    float Sound::getBalance()
    {
        return this->balance;
    }


    void Sound::setBalance(float value)
    {
        assert(value >= -1.0f && value <= 1.0f);
        this->balance = value;
    }


    float Sound::getPitch()
    {
        return this->pitch;
    }


    void Sound::setPitch(float value)
    {
        assert(value > 0.0f);
        this->pitch = value;
    }


    unsigned int Sound::getSoundId()
    {
        return this->soundId;
    }


    unsigned int Sound::getSourceId()
    {
        return this->sourceId;
    }


    void Sound::setSourceId(unsigned int value)
    {
        this->sourceId = value;
    }
}