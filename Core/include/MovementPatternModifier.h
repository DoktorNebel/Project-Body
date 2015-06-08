#pragma once

#include "IModifier.h"
#include <vector>
#include "Vector2.h"

namespace bc
{
	class MovementPatternModifier : public IModifier
	{
	public:

		struct Waypoint
		{
			se::Vector2 position;
			float speed;
			float waitTime;
			bool controlPoint;
		};

        struct Style
        {
            enum Type
            {
                Stay,
                Kill,
                Repeat,
                Reverse
            };
        };

	private:

		std::vector<Waypoint> waypoints;
        unsigned int nextWaypoint;
		float curveProgress;
		float waitTimer;
        float speed;
        Style::Type style;

    public:

        bool noRotate;

	public:

        MovementPatternModifier(std::vector<Waypoint> waypoints, float startRotation, float speed, Style::Type style);
        MovementPatternModifier(const MovementPatternModifier& other);
		~MovementPatternModifier();

    public:

        MovementPatternModifier& operator=(const MovementPatternModifier& rhs);

    private:

        void adjustWaypoints(int startPoint);

	public:

		virtual void onCreate();
		virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
	};
}