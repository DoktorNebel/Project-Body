#pragma once

#include "Engine.h"

namespace se
{
    class IGame
    {
    public:

        Engine* engine;

    public:

        virtual void initialize() = 0;
        virtual void update(float elapsedTime) = 0;
        virtual void draw() = 0;
        virtual void close() = 0;
    };
}