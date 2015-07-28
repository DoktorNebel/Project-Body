#pragma once

#include "Vector2.h"

namespace se
{
    class Camera
    {
    private:

        Vector2 position;
        float zoomFactor;
		float screenshake;
		float screenshakeDuration;
		float initialScreenshakeDuration;
        float permanentScreenshake;

    public:

        Camera();
        ~Camera();

    public:

        Vector2 getPosition();
        Vector2 getActualPosition();
        void move(Vector2 translation);
        void setPosition(Vector2 position);
        float getZoom();
        void zoom(float factor);
        void setZoom(float zoom);
		void update(float elapsedTime);
		void addScreenshake(float strength, float duration);
        void setPermanentScreenshake(float strength);
    };
}