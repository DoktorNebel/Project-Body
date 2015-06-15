#include "MovementPatternModifier.h"

#include "Entity.h"
#include "MathFunctions.h"

namespace bc
{
    MovementPatternModifier::MovementPatternModifier(std::vector<Waypoint> waypoints, float startRotation, float speed, Style::Type style)
		: waypoints(waypoints)
		, nextWaypoint(1)
		, curveProgress(0.0f)
		, waitTimer(0.0f)
        , speed(speed)
        , style(style)
        , noRotate(false)
        , shortestDistance(0.0f)
    {
        float radRot = startRotation * 0.0174532925f;
        float s = sin(radRot);
        float c = cos(radRot);
        for (unsigned int i = 0; i < this->waypoints.size(); ++i)
        {
            float newX = this->waypoints[i].position.x * c - this->waypoints[i].position.y * s;
            float newY = this->waypoints[i].position.x * s + this->waypoints[i].position.y * c;

            this->waypoints[i].position = se::Vector2(newX, newY);
        }
	}


    MovementPatternModifier::MovementPatternModifier(const MovementPatternModifier& other)
        : waypoints(other.waypoints)
        , nextWaypoint(1)
        , curveProgress(0.0f)
        , waitTimer(0.0f)
        , speed(other.speed)
        , style(other.style)
        , noRotate(other.noRotate)
        , shortestDistance(other.shortestDistance)
    {

    }


	MovementPatternModifier::~MovementPatternModifier()
	{

	}


    MovementPatternModifier& MovementPatternModifier::operator=(const MovementPatternModifier& rhs)
    {
        this->waypoints = rhs.waypoints;
        this->nextWaypoint = 1; 
        this->curveProgress = 0.0f;
        this->waitTimer = 0.0f;
        this->speed = rhs.speed;
        this->style = rhs.style;
        this->noRotate = rhs.noRotate;
        this->shortestDistance = rhs.shortestDistance;

        return *this;
    }


    void MovementPatternModifier::adjustWaypoints(int startPoint)
    {
        if ((unsigned int)startPoint < this->waypoints.size())
        {
            se::Vector2 difference = this->entity->getSprite().getPosition() - this->waypoints[startPoint].position;
            for (unsigned int i = startPoint; i < this->waypoints.size(); ++i)
            {
                this->waypoints[i].position += difference;
            }
        }
    }


	void MovementPatternModifier::onCreate()
	{
        this->adjustWaypoints(0);
        if (this->nextWaypoint < this->waypoints.size())
        {
            if (this->waypoints[this->nextWaypoint].controlPoint)
            {
                shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 1].position);
            }
            else
            {
                shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint].position);
            }
        }
	}


	void MovementPatternModifier::onUpdate(float elapsedTime)
	{
		if (this->nextWaypoint < this->waypoints.size())
		{
			if (this->waitTimer > 0.0f)
			{
                this->waitTimer -= elapsedTime * this->speed;
			}
			else if (!this->waypoints[this->nextWaypoint].controlPoint)
			{
				float factor = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint - 1].position) / se::Math::Distance(this->waypoints[this->nextWaypoint - 1].position, this->waypoints[this->nextWaypoint].position);
                float currentSpeed = se::Math::Lerp(this->waypoints[this->nextWaypoint - 1].speed, this->waypoints[this->nextWaypoint].speed, factor);
				se::Vector2 direction = se::Math::GetNormalized(this->waypoints[this->nextWaypoint].position - this->waypoints[this->nextWaypoint - 1].position);
                if (!this->noRotate)
                    this->entity->getSprite().setRotation(atan2(direction.y, direction.x) * 57.2957795f - 90.0f);
				this->entity->getSprite().move(direction * currentSpeed * elapsedTime * this->speed);

                float distance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint].position);
                if (distance <= shortestDistance)
                {
                    shortestDistance = distance;
                }
                else
                {
                    this->adjustWaypoints(this->nextWaypoint);
					this->waitTimer = this->waypoints[this->nextWaypoint].waitTime;
                    this->nextWaypoint += this->speed >= 0 ? 1 : -1; 
                    if (this->nextWaypoint < this->waypoints.size())
                    {
                        if (this->waypoints[this->nextWaypoint].controlPoint)
                        {
                            shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 1].position);
                        }
                        else
                        {
                            shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint].position);
                        }
                    }
				}
			}
			else if (this->nextWaypoint + 1 < this->waypoints.size())
			{
				se::Vector2 p1 = this->waypoints[this->nextWaypoint - 1].position + (this->waypoints[this->nextWaypoint].position - this->waypoints[this->nextWaypoint - 1].position) * this->curveProgress;
				se::Vector2 p2 = this->waypoints[this->nextWaypoint].position + (this->waypoints[this->nextWaypoint + 1].position - this->waypoints[this->nextWaypoint].position) * this->curveProgress;
                se::Vector2 newPosition = p1 + (p2 - p1) * this->curveProgress;
                se::Vector2 direction = newPosition - this->entity->getSprite().getPosition();
                if (!this->noRotate && !(direction == se::Vector2(0.0f, 0.0f)))
                    this->entity->getSprite().setRotation(atan2(direction.y, direction.x) * 57.2957795f - 90.0f);
				this->entity->getSprite().move(direction);
                float currentSpeed = se::Math::Lerp(this->waypoints[this->nextWaypoint - 1].speed, this->waypoints[this->nextWaypoint + 1].speed, this->curveProgress);
                this->curveProgress += (currentSpeed * elapsedTime * this->speed) / se::Math::Distance(this->waypoints[this->nextWaypoint - 1].position, this->waypoints[this->nextWaypoint + 1].position);

                float distance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 1].position);
                if (distance <= shortestDistance)
                {
                    shortestDistance = distance;
                }
                else
                {
                    this->adjustWaypoints(this->nextWaypoint + 1);
                    this->waitTimer = this->waypoints[this->nextWaypoint + 1].waitTime;
                    this->nextWaypoint += this->speed >= 0 ? 1 : -1;
                    this->curveProgress = 0.0f;
                    if (this->nextWaypoint + 1 < this->waypoints.size())
                    {
                        if (this->waypoints[this->nextWaypoint + 1].controlPoint)
                        {
                            shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 2].position);
                        }
                        else
                        {
                            shortestDistance = se::Math::Distance(this->entity->getSprite().getPosition(), this->waypoints[this->nextWaypoint + 1].position);
                        }
                    }
				}
			}
		}
		else
		{
            switch (this->style)
            {
            case Style::Kill:
                this->entity->health = 0.0f;
                break;

            case Style::Repeat:
                this->nextWaypoint = 1;
                this->entity->getSprite().setPosition(this->waypoints[0].position);
                this->curveProgress = 0.0f;
                break;

            case Style::Reverse:
                this->speed *= -1;

            }
		}
	}


    void MovementPatternModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
	{

	}
}