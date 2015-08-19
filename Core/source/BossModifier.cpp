#include "BossModifier.h"

#include "Entity.h"
#include "BossPartModifier.h"
#include "Spawner.h"
#include "HitMarkerModifier.h"
#include "MathFunctions.h"
#include "GameData.h"
#include "Engine.h"
#include "MenuData.h"
#include "CoinModifier.h"
#include "AnimationModifier.h"
#include "MenuScene.h"
#include "UIText.h"

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
        se::Engine::getMenu()->getElement("UI", "BossbarText")->show();
        for (int i = 0; i < 100; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            se::Engine::getMenu()->getElement("UI", "Bossbar" + std::string(number))->show();
        }

		this->explodingTimer = 5.0f;
		this->dying = false;
    }


    void BossModifier::onUpdate(float elapsedTime)
    {
        float healthPercentage = this->entity->health / this->entity->maxHealth;

        ((bg::MenuData*)se::Engine::getMenu()->data)->bossHealth = healthPercentage;

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
                modifiers.push_back(new BossPartModifier(this, this->phases[this->nextPhase].parts[i].health, this->phases[this->nextPhase].parts[i].spriteName));
                this->parts.push_back((BossPartModifier*)modifiers.back());
                modifiers.push_back(new HitMarkerModifier());
                if (this->phases[this->nextPhase].parts[i].movePatternName != "None")
                {
                    modifiers.push_back(new MovementPatternModifier(Spawner::getMovementPattern(this->phases[this->nextPhase].parts[i].movePatternName), 0.0f, 1.0f, this->phases[this->nextPhase].parts[i].movementType));
                    if (this->phases[this->nextPhase].parts[i].noRotate)
                        ((MovementPatternModifier*)modifiers.back())->noRotate = true;
                }
                if (this->phases[this->nextPhase].parts[i].shotPatternName != "None")
                    modifiers.push_back(new ShootingModifier(Spawner::getShotPattern(this->phases[this->nextPhase].parts[i].shotPatternName)));
                Spawner::spawn(this->entity->getSprite().getPosition() + this->phases[this->nextPhase].parts[i].spawnPosition, this->phases[this->nextPhase].parts[i].spriteName, modifiers, CollisionGroup::Enemies);
            }

            if (healthPercentage != 1.0f)
            {
                this->deleteBullets();
                se::Engine::getActiveCamera().addScreenshake(10.0f, 1.0f);

                se::AnimatedSprite coinSprite;
                coinSprite.addAnimation("Idle");
                coinSprite.setSpeed("Idle", 0.2f);
                coinSprite.addSprite("Idle", se::Content::getSprite("M1"));
                coinSprite.addSprite("Idle", se::Content::getSprite("M2"));
                coinSprite.addSprite("Idle", se::Content::getSprite("M3"));
                coinSprite.addSprite("Idle", se::Content::getSprite("M4"));
                coinSprite.setScale(se::Vector2(3.0f, 3.0f));
                std::vector<IModifier*> modifiers;
                for (unsigned int i = 0; i < 200; ++i)
                {
                    modifiers.clear();
                    modifiers.push_back(new CoinModifier(1));
                    modifiers.push_back(new AnimationModifier(coinSprite));
                    Spawner::spawn(this->entity->getSprite().getPosition(), "M1", modifiers, CollisionGroup::Items);
                }
            }

            ++this->nextPhase;
        }

        if (this->entity->health <= 0.0f)
        {
			if (!this->dying)
			{
				this->dying = true;
				this->entity->modifiers.erase(std::find_if(this->entity->modifiers.begin(), this->entity->modifiers.end(), [](IModifier*& modifier)
				{
					return dynamic_cast<ShootingModifier*>(modifier);
                }));
                this->deleteBullets();
                se::Engine::getActiveCamera().addScreenshake(15.0f, 1.0f);
			}
			this->explodingTimer -= elapsedTime;
			if (this->explodingTimer <= -3.0f)
			{
				this->entity->dead = true;
                se::Engine::getMenu()->changeMenu("LevelEnd");
                se::Sprite background = se::Content::getSprite("flesh");
                bg::MenuScene* newScene = new bg::MenuScene(background);
                se::Engine::changeScene(newScene);
                char scoreString[16];
                _itoa(GameData::score, scoreString, 10);
                ((se::UIText*)se::Engine::getMenu()->getElement("LevelEnd", "ScoreText"))->getText().setText("Score: " + std::string(scoreString));
			}
            else if (this->explodingTimer > 0.0f)
			{
				this->coinTimer += elapsedTime;
				while (this->coinTimer >= 0.0f)
				{
					this->coinTimer -= 0.01f;

					se::AnimatedSprite coinSprite;
					coinSprite.addAnimation("Idle");
					coinSprite.setSpeed("Idle", 0.2f);
					coinSprite.addSprite("Idle", se::Content::getSprite("M1"));
					coinSprite.addSprite("Idle", se::Content::getSprite("M2"));
					coinSprite.addSprite("Idle", se::Content::getSprite("M3"));
					coinSprite.addSprite("Idle", se::Content::getSprite("M4"));
					coinSprite.setScale(se::Vector2(3.0f, 3.0f));
					std::vector<IModifier*> modifiers;
					modifiers.push_back(new CoinModifier(1));
					modifiers.push_back(new AnimationModifier(coinSprite));
					Spawner::spawn(this->entity->getSprite().getPosition(), "M1", modifiers, CollisionGroup::Items);
				}
			}
            else
            {
                this->entity->getSprite().setScale(se::Vector2(0.0f, 0.0f));
                Spawner::bossAlive = false;
            }
        }
    }


    void BossModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }


    void BossModifier::destroyPart(BossPartModifier* part)
    {
        part->entity->dead = true;
        this->parts.erase(std::find(this->parts.begin(), this->parts.end(), part));
    }


    void BossModifier::deleteBullets()
    {
        std::vector<Entity>* projectiles = Spawner::getEntities(CollisionGroup::EnemyProjectiles);

        se::AnimatedSprite coinSprite;
        coinSprite.addAnimation("Idle");
        coinSprite.setSpeed("Idle", 0.2f);
        coinSprite.addSprite("Idle", se::Content::getSprite("M1"));
        coinSprite.addSprite("Idle", se::Content::getSprite("M2"));
        coinSprite.addSprite("Idle", se::Content::getSprite("M3"));
        coinSprite.addSprite("Idle", se::Content::getSprite("M4"));
        coinSprite.setScale(se::Vector2(3.0f, 3.0f));
        std::vector<IModifier*> modifiers;

        for (unsigned int i = 0; i < projectiles->size(); ++i)
        {
            modifiers.clear();
            modifiers.push_back(new CoinModifier(1));
            modifiers.push_back(new AnimationModifier(coinSprite));
            Spawner::spawn((*projectiles)[i].getSprite().getPosition(), "M1", modifiers, CollisionGroup::Items);

            (*projectiles)[i].dead = true;
        }
    }
}