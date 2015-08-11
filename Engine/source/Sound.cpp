#include "Sound.h"

namespace se
{
    Sound::Sound(unsigned int soundId)
        : state(Sound::State::Stopped)
        , looping(false)
        , soundId(soundId)
    {

    }


    Sound::State::Type Sound::getState()
    {
        return this->state;
    }


    void Sound::setState(State::Type state)
    {
        this->state = state;
    }


    bool Sound::getLooping()
    {
        return this->looping;
    }


    void Sound::setLooping(bool value)
    {
        this->looping = value;
    }


    unsigned int Sound::getSoundId()
    {
        return this->soundId;
    }
}