#include "Level.h"

#include "Spawner.h"
#include "Content.h"
#include "PlayerModifier.h"
#include "EnemyModifier.h"

namespace bc
{
    Level::Level()
    {

    }


    Level::~Level()
    {

    }


    void Level::initialize(std::string source)
    {

        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::EnemyProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Enemies));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Items));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Enemies, CollisionGroup::PlayerProjectiles));
        
        se::Engine::setActiveCamera(this->camera);

        this->entities.resize(7);
        this->hitboxes.resize(7);

        Spawner::initialize(&this->hitboxes, &this->entities);

        std::vector<IModifier*> modifiers;
        modifiers.push_back(new PlayerModifier());
        Spawner::spawn(se::Vector2(0, -200), Entity(se::Content::getSprite("TestPlayer"), modifiers), CollisionGroup::Players);

        this->spawn = 0.1f;
    }


    void Level::update(float elapsedTime)
    {
        std::vector<Entity>::iterator entIter;
        std::vector<Entity>::iterator entEnd;
        std::vector<se::Rectangle>::iterator rectIter;

        for (int i = 0; i < this->entities.size(); ++i)
        {
            entIter = this->entities[i].begin();
            entEnd = this->entities[i].end();
            rectIter = this->hitboxes[i].begin();
            while (entIter != entEnd)
            {
                entIter->update(elapsedTime);
                if (entIter->isDead())
                {
                    entIter = this->entities[i].erase(entIter);
                    entEnd = this->entities[i].end();
                    rectIter = this->hitboxes[i].erase(rectIter);
                }
                else
                {
                    *rectIter = entIter->getHitbox();
                    ++entIter;
                    ++rectIter;
                }
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
                        this->entities[this->collisionConfigs[i].first][j].hit(&this->entities[this->collisionConfigs[i].second][k], this->collisionConfigs[i].second);
                        this->entities[this->collisionConfigs[i].second][k].hit(&this->entities[this->collisionConfigs[i].first][j], this->collisionConfigs[i].first);
                    }
                }
            }
        }

        this->spawn -= elapsedTime;
        if (this->spawn <= 0.0f)
        {
            this->spawn = 0.1f;
            std::vector<IModifier*> modifiers;
            modifiers.push_back(new EnemyModifier());
            Spawner::spawn(se::Vector2(rand() % 501 - 250, 400), bc::Entity(se::Content::getSprite("Virus1"), modifiers), CollisionGroup::Enemies);
        }

        Spawner::update(elapsedTime);

        this->camera.update(elapsedTime);
    }


    void Level::draw()
    {
        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                se::Engine::draw(this->entities[i][j].getSprite());
            }
        }
    }
}