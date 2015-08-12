#pragma once

namespace se
{
    class Sound
    {
    private:

        bool looping;
        float volume;
        float balance;
        float pitch;
        unsigned int soundId;
        unsigned int sourceId;

    public:

        Sound(unsigned int soundId = 0);

    public:

        bool getLooping();
        void setLooping(bool value);
        float getVolume();
        void setVolume(float value);
        float getBalance();
        void setBalance(float value);
        float getPitch();
        void setPitch(float value);
        unsigned int getSoundId();
        unsigned int getSourceId();
        void setSourceId(unsigned int value);
    };
}