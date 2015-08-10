#pragma once

namespace se
{
    class Sound
    {
    public:

        struct State
        {
            enum Type
            {
                Playing,
                Paused,
                Stopped
            };
        };

    private:

        State::Type state;
        bool looping;
        unsigned int soundId;

    public:

        Sound(unsigned int soundId = 0);

    public:

        State::Type getState();
        void setState(State::Type state);
        bool getLooping();
        void setLooping();
        unsigned int getSoundId();
    };
}