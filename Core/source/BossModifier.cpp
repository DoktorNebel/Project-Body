#include "BossModifier.h"

#include "Entity.h"
#include "BossPartModifier.h"
#include "Spawner.h"
#include "HitMarkerModifier.h"
#include "MathFunctions.h"

namespace bc
{
    BossModifier::BossModifier(std::vector<Phase> pattern)
        : phases(pattern)
        , nextPhase(0)
    {

    }


    void BossModifier::onCreate()
    {
        Spawner::bossAlive = true;
    }


    void BossModifier::onUpdate(float elapsedTime)
    {
        float healthPercentage = this->entity->health / this->entity->maxHealth;

        if (this->nextPhase < this->phases.size() && healthPercentage <= this->phases[this->nextPhase].startHealth)
        {
            //remove old movement and shooting
            std::vector<IModifier*>::iterator iter = this->entity->modifiers.begin();
            while (iter != this->entity->modifiers.end())
            {
                if (dynamic_cast<MovementPatternModifier*>(*iter) || dynamic_cast<ShootingModifier*>(*iter))
                {
                    delete *iter;
                    iter = this->entity->modifiers.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }

            //create new movement and shooting
            this->entity->modifiers.push_back(new MovementPatternModifier(Spawner::getMovementPattern(this->phases[this->nextPhase].movementPattern), 0.0f, 1.0f, this->phases[this->nextPhase].movementType));
            this->entity->modifiers.back()->entity = this->entity;
            this->entity->modifiers.back()->onCreate();
            this->entity->modifiers.push_back(new ShootingModifier(Spawner::getShotPattern(this->phases[this->nextPhase].shotPattern)));
            this->entity->modifiers.back()->entity = this->entity;
            this->entity->modifiers.back()->onCreate();

            //destroy old parts
            for (unsigned int i = 0; i < this->parts.size(); ++i)
            {
                this->parts[i]->entity->dead = true;
            }
            this->parts.clear();

            //create new parts
            for (unsigned int i = 0; i < this->phases[this->nextPhase].parts.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new BossPartModifier(this));
                this->parts.push_back((BossPartModifier*)modifiers.back());
                modifiers.push_back(new HitMarkerModifier());
                if (this->phases[this->nextPhase].parts[i].movePatternName != "")
                {
                    modifiers.push_back(new MovementPatternModifier(Spawner::getMovementPattern(this->phases[this->nextPhase].parts[i].movePatternName), 0.0f, 1.0f, MovementPatternModifier::Style::Stay));
                    if (this->phases[this->nextPhase].parts[i].noRotate)
                        ((MovementPatternModifier*)modifiers.back())->noRotate = true;
                }
                if (this->phases[this->nextPhase].parts[i].shotPatternName != "")
                    modifiers.push_back(new ShootingModifier(Spawner::getShotPattern(this->phases[this->nextPhase].parts[i].shotPatternName)));
                Spawner::spawn(this->entity->getSprite().getPosition() + this->phases[this->nextPhase].parts[i].spawnPosition, this->phases[this->nextPhase].parts[i].spriteName, modifiers, CollisionGroup::Enemies);
            }

            ++this->nextPhase;
        }

        if (this->entity->health <= 0.0f)
        {
            this->entity->dead = true;
            Spawner::bossAlive = false;
        }
    }


    void BossModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}