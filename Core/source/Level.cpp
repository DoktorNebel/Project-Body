#include "Level.h"

#include "Spawner.h"
#include "Content.h"
#include "PlayerModifier.h"

namespace bc
{
    Level::Level()
    {

    }


    Level::~Level()
    {

    }


    void Level::initialize(std::string source, se::Engine* engine)
    {
        this->engine = engine;

        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::EnemyProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Enemies));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Items));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Enemies, CollisionGroup::PlayerProjectiles));
        
        this->engine->setActiveCamera(this->camera);

        this->entities.resize(6);
        this->hitboxes.resize(6);

        Spawner::initialize(&this->hitboxes, &this->entities);

        std::vector<IModifier*> modifiers;
        modifiers.push_back(new PlayerModifier());
        Spawner::spawn(se::Vector2(0, -200), Entity(se::Content::getSprite("StaminaBar"), modifiers), CollisionGroup::Players);
    }


    void Level::update(float elapsedTime)
    {
        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                this->entities[i][j].update(elapsedTime);
                this->hitboxes[i][j] = this->entities[i][j].getHitbox();
            }
        }


        //collision detection
        for (int i = 0; i < this->collisionConfigs.size(); ++i)
        {
            for (int j = 0; j < this->hitboxes[this->collisionConfigs[i].first].size(); ++j)
            {
                for (int k = 0; k < this->hitboxes[this->collisionConfigs[i].second].size(); ++k)
                {
                    if (this->hitboxes[this->collisionConfigs[i].first][j].overlap(this->hitboxes[this->collisionConfigs[i].second][k]))
                    {
                        this->entities[this->collisionConfigs[i].first][j].hit(&this->entities[this->collisionConfigs[i].second][k]);
                        this->entities[this->collisionConfigs[i].second][k].hit(&this->entities[this->collisionConfigs[i].first][j]);
                    }
                }
            }
        }

        Spawner::update(elapsedTime);
    }


    void Level::draw()
    {
        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                this->engine->draw(this->entities[i][j].getSprite());
            }
        }
    }
}