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

	private:

		std::vector<Waypoint> waypoints;
		int nextWaypoint;
		float curveProgress;
		float waitTimer;

	public:

		MovementPatternModifier(std::vector<Waypoint> waypoints);
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