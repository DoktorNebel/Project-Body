#include "Camera.h"

#include "MathFunctions.h"
#include <random>

namespace se
{
    Camera::Camera()
        : position(0, 0)
        , zoomFactor(1.0f)
		, screenshake(0.0f)
		, screenshakeDuration(0.0f)
		, initialScreenshakeDuration(0.0f)
    {

    }


    Camera::~Camera()
    {

    }


    Vector2 Camera::getPosition()
    {
		Vector2 displacement = this->screenshakeDuration > 0.0f ? Vector2(rand() % (this->screenshake + 1) - this->screenshake / 2, rand() % (this->screenshake + 1) - this->screenshake / 2) * (this->screenshakeDuration / this->initialScreenshakeDuration) * 0.01f : Vector2();
		return this->position + displacement;
    }


    void Camera::move(Vector2 translation)
    {
        this->position += translation;
    }


    void Camera::setPosition(Vector2 position)
    {
        this->position = position;
    }


    float Camera::getZoom()
    {
        return this->zoomFactor;
    }


    void Camera::zoom(float factor)
    {
        this->zoomFactor *= factor;
    }


    void Camera::setZoom(float zoom)
    {
        this->zoomFactor = zoom;
    }


	void Camera::update(float elapsedTime)
	{
		if (this->screenshakeDuration > 0.0f)
			this->screenshakeDuration -= elapsedTime;
		else
			this->screenshake = 0.0f;
	}


	void Camera::addScreenshake(int strength, float duration)
	{
		this->screenshake += strength;
		this->screenshakeDuration = this->initialScreenshakeDuration = duration;
	}
}