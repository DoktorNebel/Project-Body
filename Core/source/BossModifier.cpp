#include "BossModifier.h"

#include "Entity.h"
#include "BossPartModifier.h"
#include "Spawner.h"
#include "HitMarkerModifier.h"

namespace bc
{
    BossModifier::BossModifier(std::vector<Phase> pattern)
        : phases(pattern)
    {

    }


    void BossModifier::onCreate()
    {

    }


    void BossModifier::onUpdate(float elapsedTime)
    {
        float healthPercentage = this->entity->health / this->entity->maxHealth;

        if (this->nextPhase < this->phases.size() && healthPercentage <= this->phases[this->nextPhase].startHealth)
        {
            for (int i = 0; i < this->parts.size(); ++i)
            {
                this->parts[i]->entity->dead = true;
            }
            this->parts.clear();

            for (int i = 0; i < this->phases[this->nextPhase].parts.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new BossPartModifier(this));
                modifiers.push_back(new HitMarkerModifier());
                if (this->phases[this->nextPhase].parts[i].movePatternName != "")
                    modifiers.push_back(new MovementPatternModifier(Spawner::getMovementPattern(this->phases[this->nextPhase].parts[i].movePatternName), 0.0f, 1.0f, MovementPatternModifier::Style::Stay));
                if (this->phases[this->nextPhase].parts[i].shotPatternName != "")
                    modifiers.push_back(new ShootingModifier(Spawner::getShotPattern(this->phases[this->nextPhase].parts[i].shotPatternName)));
                Spawner::spawn(this->phases[this->nextPhase].parts[i].spawnPosition, this->phases[this->nextPhase].parts[i].spriteName, modifiers, CollisionGroup::Enemies);
            }

            for (int i = 0; i < this->entity->modifiers.size(); ++i)
            {
                if (dynamic_cast<ShootingModifier*>(this->entity->modifiers[i]))
                {
                    delete this->entity->modifiers[i];
                    this->entity->modifiers.erase(this->entity->modifiers.begin() + i);
                }
            }

            ++this->nextPhase;
        }

        if (this->entity->health <= 0.0f)
            this->entity->dead = true;
    }


    void BossModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}