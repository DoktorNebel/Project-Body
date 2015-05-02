#pragma once

#include "Vector2.h"

namespace se
{
    class Camera
    {
    private:

        Vector2 position;
        float zoomFactor;
		int screenshake;
		float screenshakeDuration;
		float initialScreenshakeDuration;

    public:

        Camera();
        ~Camera();

    public:

        Vector2 getPosition();
        void move(Vector2 translation);
        void setPosition(Vector2 position);
        float getZoom();
        void zoom(float factor);
        void setZoom(float zoom);
		void update(float elapsedTime);
		void addScreenshake(int strength, float duration);
    };
}