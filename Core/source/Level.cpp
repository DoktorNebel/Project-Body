#include "Level.h"

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

        this->collisionConfigs.push_back(std::pair<Index::Type, Index::Type>(Index::Players, Index::EnemyProjectiles));
        this->collisionConfigs.push_back(std::pair<Index::Type, Index::Type>(Index::Players, Index::Enemies));
        this->collisionConfigs.push_back(std::pair<Index::Type, Index::Type>(Index::Players, Index::Items));
        this->collisionConfigs.push_back(std::pair<Index::Type, Index::Type>(Index::Players, Index::LevelElements));
        this->collisionConfigs.push_back(std::pair<Index::Type, Index::Type>(Index::Enemies, Index::PlayerProjectiles));

        this->engine->setActiveCamera(this->camera);

        this->entities.resize(6);
        this->entities[Index::Players].push_back(new Player());
        this->hitboxes.resize(this->entities.size());
        this->hitboxes[Index::Players].resize(1);
    }


    void Level::update(float elapsedTime)
    {
        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                this->entities[i][j]->update(elapsedTime);
                this->hitboxes[i][j] = this->entities[i][j]->getHitbox();
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
                        switch (this->collisionConfigs[i].second)
                        {
                        case Index::Enemies:
                            this->entities[this->collisionConfigs[i].first][j]->hit((Enemy*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        case Index::EnemyProjectiles:
                            this->entities[this->collisionConfigs[i].first][j]->hit((Projectile*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        case Index::PlayerProjectiles:
                            this->entities[this->collisionConfigs[i].first][j]->hit((Projectile*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        case Index::Items:
                            this->entities[this->collisionConfigs[i].first][j]->hit((Item*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        case Index::LevelElements:
                            this->entities[this->collisionConfigs[i].first][j]->hit((LevelElement*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        case Index::Players:
                            this->entities[this->collisionConfigs[i].first][j]->hit((Player*)this->entities[this->collisionConfigs[i].second][k]);
                            break;
                        }

                        switch (this->collisionConfigs[i].first)
                        {
                        case Index::Players:
                            this->entities[this->collisionConfigs[i].second][k]->hit((Player*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        case Index::Enemies:
                            this->entities[this->collisionConfigs[i].second][k]->hit((Enemy*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        case Index::EnemyProjectiles:
                            this->entities[this->collisionConfigs[i].second][k]->hit((Projectile*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        case Index::PlayerProjectiles:
                            this->entities[this->collisionConfigs[i].second][k]->hit((Projectile*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        case Index::Items:
                            this->entities[this->collisionConfigs[i].second][k]->hit((Item*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        case Index::LevelElements:
                            this->entities[this->collisionConfigs[i].second][k]->hit((LevelElement*)this->entities[this->collisionConfigs[i].first][j]);
                            break;
                        }
                    }
                }
            }
        }
    }


    void Level::draw()
    {
        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                this->engine->draw(this->entities[i][j]->getSprite());
            }
        }
    }
}