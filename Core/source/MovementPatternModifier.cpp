#include "MovementPatternModifier.h"

#include "Entity.h"
#include "MathFunctions.h"

namespace bc
{
	MovementPatternModifier::MovementPatternModifier(std::vector<Waypoint> waypoints)
		: waypoints(waypoints)
		, nextWaypoint(1)
		, curveProgress(0.0f)
		, waitTimer(0.0f)
	{

	}


	MovementPatternModifier::~MovementPatternModifier()
	{

	}


	void MovementPatternModifier::onCreate()
	{
		for (int i = 0; i < this->waypoints.size(); ++i)
		{
			this->waypoints[i].position += this->entity->getSprite().getPosition();
		}
	}


	void MovementPatternModifier::onUpdate(float elapsedTime)
	{
		if (this->nextWaypoint < this->waypoints.size())
		{
			if (this->waitTimer > 0.0f)
			{
				this->waitTimer -= elapsedTime;
			}
			else if (!this->waypoints[this->nextWaypoint].controlPoint)
			{
				float factor = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint - 1].position) / se::Math::Distance(this->waypoints[this->nextWaypoint - 1].position, this->waypoints[this->nextWaypoint].position);
				float currentSpeed = se::Math::Lerp(this->waypoints[this->nextWaypoint - 1].speed, this->waypoints[this->nextWaypoint].speed, factor);
				se::Vector2 direction = se::Math::GetNormalized(this->waypoints[this->nextWaypoint].position - this->waypoints[this->nextWaypoint - 1].position);
				this->entity->getSprite().move(direction * currentSpeed * elapsedTime);

				if (se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint].position) <= 1.0f)
				{
					this->waitTimer = this->waypoints[this->nextWaypoint].waitTime;
					++this->nextWaypoint;
				}
			}
			else if (this->nextWaypoint + 1 < this->waypoints.size())
			{
				se::Vector2 p1 = this->waypoints[this->nextWaypoint - 1].position + (this->waypoints[this->nextWaypoint].position - this->waypoints[this->nextWaypoint - 1].position) * this->curveProgress;
				se::Vector2 p2 = this->waypoints[this->nextWaypoint].position + (this->waypoints[this->nextWaypoint + 1].position - this->waypoints[this->nextWaypoint].position) * this->curveProgress;
				se::Vector2 newPosition = p1 + (p2 - p1) * this->curveProgress;
				this->entity->getSprite().setPosition(newPosition);
				float currentSpeed = se::Math::Lerp(this->waypoints[this->nextWaypoint - 1].speed, this->waypoints[this->nextWaypoint + 1].speed, this->curveProgress);
				this->curveProgress += currentSpeed * elapsedTime;

				if (se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 1].position) <= 1.0f)
				{
					this->waitTimer = this->waypoints[this->nextWaypoint + 1].waitTime;
					++this->nextWaypoint;
				}
			}
		}
		else
		{
			this->entity->dead = true;
		}
	}


	void MovementPatternModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup)
	{

	}
}