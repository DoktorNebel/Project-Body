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
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::PlayerProjectiles, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Enemies, CollisionGroup::PlayerProjectiles));
        
        se::Engine::setActiveCamera(this->camera);

        this->entities.resize(7);
        this->hitboxes.resize(7);

        Spawner::initialize(&this->hitboxes, &this->entities, source);

        std::vector<IModifier*> modifiers;
        modifiers.push_back(new PlayerModifier(&this->entities));
        Spawner::spawn(se::Vector2(0, -200), Entity(se::Content::getSprite("TestPlayer"), modifiers), CollisionGroup::Players);

        this->totalElapsedTime = 0.0f;
        this->currentScrollKey = 0;

        ScrollKey key;
        key.time = 0.0f;
        key.speed = 0.0f;
        this->scrollSpeeds.push_back(key);
        key.time = 5.0f;
        key.speed = 300.0f;
        this->scrollSpeeds.push_back(key);
        key.time = 10.0f;
        key.speed = 1000.0f;
        this->scrollSpeeds.push_back(key);
        key.time = 15.0f;
        key.speed = 300.0f;
        this->scrollSpeeds.push_back(key);
        key.time = 120.0f;
        key.speed = 100.0f;
        this->scrollSpeeds.push_back(key);

        this->backgroundSpeeds.push_back(1.0f);
        this->backgroundSpeeds.push_back(0.8f);
        this->backgroundSpeeds.push_back(0.6f);
        this->backgroundSpeeds.push_back(0.4f);

        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        for (int i = 0; i < 50; ++i)
        {
            this->backgroundSprites[0].push_back(se::Content::getSprite("BG-Tile-1-Links"));
            this->backgroundSprites[0].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[0].back().setPosition(se::Vector2(-this->backgroundSprites[0].back().getWidth() * this->backgroundSprites[0].back().getScale().x, -this->backgroundSprites[0].back().getHeight() / 2 * this->backgroundSprites[0].back().getScale().y + i * 256 * this->backgroundSprites[0].back().getScale().y));
            this->backgroundSprites[0].back().setDepth(0.5f);
            this->backgroundSprites[0].push_back(se::Content::getSprite("BG-Tile-1-Rechts"));
            this->backgroundSprites[0].back() = this->backgroundSprites[0].back();
            this->backgroundSprites[0].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[0].back().setPosition(se::Vector2(this->backgroundSprites[0].back().getWidth() * this->backgroundSprites[0].back().getScale().x, -this->backgroundSprites[0].back().getHeight() / 2 * this->backgroundSprites[0].back().getScale().y + i * 256 * this->backgroundSprites[0].back().getScale().y));
            this->backgroundSprites[0].back().setDepth(0.5f);
        }
        for (int i = 0; i < 25; ++i)
        {
            this->backgroundSprites[1].push_back(se::Content::getSprite("BG-Tile-2"));
            this->backgroundSprites[1].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[1].back().setPosition(se::Vector2(0.0f, i * 512 * this->backgroundSprites[1].back().getScale().y));
            this->backgroundSprites[1].back().setDepth(0.6f);

            this->backgroundSprites[2].push_back(se::Content::getSprite("BG-Tile-3"));
            this->backgroundSprites[2].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[2].back().setPosition(se::Vector2(0.0f, i * 512 * this->backgroundSprites[2].back().getScale().y));
            this->backgroundSprites[2].back().setDepth(0.7f);

            this->backgroundSprites[3].push_back(se::Content::getSprite("BG-Tile-4"));
            this->backgroundSprites[3].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[3].back().setPosition(se::Vector2(0.0f, i * 511 * this->backgroundSprites[3].back().getScale().y));
            this->backgroundSprites[3].back().setDepth(0.8f);
        }
    }


    void Level::update(float elapsedTime)
    {
        std::vector<Entity>::iterator entIter;
        std::vector<Entity>::iterator entEnd;
        std::vector<se::Rectangle>::iterator rectIter;

        //updating
        for (int i = 0; i < this->entities.size(); ++i)
        {
            entIter = this->entities[i].begin();
            entEnd = this->entities[i].end();
            rectIter = this->hitboxes[i].begin();
            while (entIter != entEnd)
            {
                entIter->update(elapsedTime);
                if (entIter->dead)
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

        Spawner::update(elapsedTime);

        //background scrolling
        this->totalElapsedTime += elapsedTime;

        if (this->entities[CollisionGroup::Players].size() > 0)
            this->camera.setPosition(se::Vector2(this->entities[CollisionGroup::Players][0].getSprite().getPosition().x / se::Engine::getSettings().resolutionWidth, 0.0f));

        float currentScrollSpeed = 0.0f;
        if (this->currentScrollKey + 1 < this->scrollSpeeds.size())
        {
            float factor = (this->totalElapsedTime - this->scrollSpeeds[this->currentScrollKey].time) / (this->scrollSpeeds[this->currentScrollKey + 1].time - this->scrollSpeeds[this->currentScrollKey].time);
            currentScrollSpeed = (1 - factor) * this->scrollSpeeds[this->currentScrollKey].speed + factor * this->scrollSpeeds[this->currentScrollKey + 1].speed;
            
            if (this->totalElapsedTime > this->scrollSpeeds[this->currentScrollKey + 1].time)
                ++this->currentScrollKey;
        }

        for (int i = 0; i < this->backgroundSprites.size(); ++i)
        {
            for (int j = 0; j < this->backgroundSprites[i].size(); ++j)
            {
                this->backgroundSprites[i][j].move(se::Vector2(0.0f, currentScrollSpeed * -this->backgroundSpeeds[i] * elapsedTime));
            }
        }

        for (int i = 0; i < this->entities[CollisionGroup::LevelElements].size(); ++i)
        {
            this->entities[CollisionGroup::LevelElements][i].getSprite().move(se::Vector2(0.0f, -currentScrollSpeed * elapsedTime));
        }

        this->camera.update(elapsedTime);
    }


    void Level::draw()
    {
        for (int i = 0; i < this->backgroundSprites.size(); ++i)
        {
            for (int j = 0; j < this->backgroundSprites[i].size(); ++j)
            {
                se::Engine::draw(this->backgroundSprites[i][j]);
            }
        }

        for (int i = 0; i < this->entities.size(); ++i)
        {
            for (int j = 0; j < this->entities[i].size(); ++j)
            {
                se::Engine::draw(this->entities[i][j].getSprite());
            }
        }
    }
}