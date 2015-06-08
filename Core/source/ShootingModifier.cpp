#include "ShootingModifier.h"

#include "Spawner.h"
#include "ProjectileModifier.h"
#include "MovementPatternModifier.h"
#include "AnimationModifier.h"

namespace bc
{
    ShootingModifier::ShootingModifier(ShotPattern pattern)
        : shotPattern(pattern)
    {

    }


    void ShootingModifier::onCreate()
    {

    }


    void ShootingModifier::onUpdate(float elapsedTime)
    {
        this->timer += elapsedTime;
        if (this->timer >= this->shotPattern.delays[this->currentSalvo])
        {
            this->timer = 0.0f;

            for (unsigned int i = 0; i < this->shotPattern.shotSalvos[this->currentSalvo].shotMovementNames.size(); ++i)
            {
                std::vector<IModifier*> modifiers;
                modifiers.push_back(new ProjectileModifier(se::Vector2(0.0f, 0.0f), 5.0f));
                modifiers.push_back(new MovementPatternModifier(Spawner::getMovementPattern(this->shotPattern.shotSalvos[this->currentSalvo].shotMovementNames[i]), this->shotPattern.shotSalvos[this->currentSalvo].rotations[i], this->shotPattern.shotSalvos[this->currentSalvo].speeds[i], MovementPatternModifier::Style::Kill));
                se::AnimatedSprite sprite;
                bool result;
                if (result = Spawner::getAnimation(this->shotPattern.shotSalvos[this->currentSalvo].shotSpriteNames[i], &sprite))
                {
                    modifiers.push_back(new AnimationModifier(sprite));
                }
                Spawner::spawn(this->entity->getSprite().getPosition(), result ? this->shotPattern.shotSalvos[this->currentSalvo].shotSpriteNames[i] + "0" : this->shotPattern.shotSalvos[this->currentSalvo].shotSpriteNames[i], modifiers, CollisionGroup::EnemyProjectiles);
            }

            ++this->currentSalvo;
            if (this->currentSalvo >= this->shotPattern.delays.size())
                this->currentSalvo = 0;
        }
    }


    void ShootingModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}