#include "Level.h"

#include "Spawner.h"
#include "Content.h"
#include "PlayerModifier.h"
#include "EnemyModifier.h"
#include "MathFunctions.h"
#include "Input.h"
#include "InputActions.h"
#include "GameData.h"

namespace bc
{
    Level::Level()
        : medicineBox(0)
    {

    }


    Level::~Level()
    {

    }


    void Level::createBackgrounds(Tileset::Type tileset, int length)
    {
        std::string bgTile1Left;
        std::string bgTile1Right;
        std::string bgTile2;
        std::string bgTile3;
        std::string bgTile4;

        switch (tileset)
        {
        case Tileset::Flesh:
            bgTile1Left = "BG-Tile-1-Links";
            bgTile1Right = "BG-Tile-1-Rechts";
            bgTile2 = "BG-Tile-2";
            bgTile3 = "BG-Tile-3";
            bgTile4 = "BG-Tile-4";
            break;
        }


        for (int i = 0; i < length * 2; ++i)
        {
            this->backgroundSprites[0].push_back(se::Content::getSprite(bgTile1Left));
            this->backgroundSprites[0].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[0].back().setPosition(se::Vector2(-this->backgroundSprites[0].back().getWidth() * this->backgroundSprites[0].back().getScale().x, -this->backgroundSprites[0].back().getHeight() / 2 * this->backgroundSprites[0].back().getScale().y + i * 256 * this->backgroundSprites[0].back().getScale().y));
            this->backgroundSprites[0].back().setDepth(0.5f);
            this->backgroundSprites[0].push_back(se::Content::getSprite(bgTile1Right));
            this->backgroundSprites[0].back() = this->backgroundSprites[0].back();
            this->backgroundSprites[0].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[0].back().setPosition(se::Vector2(this->backgroundSprites[0].back().getWidth() * this->backgroundSprites[0].back().getScale().x, -this->backgroundSprites[0].back().getHeight() / 2 * this->backgroundSprites[0].back().getScale().y + i * 256 * this->backgroundSprites[0].back().getScale().y));
            this->backgroundSprites[0].back().setDepth(0.5f);
        }
        for (int i = 0; i < length; ++i)
        {
            this->backgroundSprites[1].push_back(se::Content::getSprite(bgTile2));
            this->backgroundSprites[1].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[1].back().setPosition(se::Vector2(0.0f, i * 512 * this->backgroundSprites[1].back().getScale().y));
            this->backgroundSprites[1].back().setDepth(0.6f);

            this->backgroundSprites[2].push_back(se::Content::getSprite(bgTile3));
            this->backgroundSprites[2].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[2].back().setPosition(se::Vector2(0.0f, i * 512 * this->backgroundSprites[2].back().getScale().y));
            this->backgroundSprites[2].back().setDepth(0.7f);

            this->backgroundSprites[3].push_back(se::Content::getSprite(bgTile4));
            this->backgroundSprites[3].back().setScale(se::Vector2(3.0f, 3.0f));
            this->backgroundSprites[3].back().setPosition(se::Vector2(0.0f, i * 511 * this->backgroundSprites[3].back().getScale().y));
            this->backgroundSprites[3].back().setDepth(0.8f);
        }
    }


    void Level::initializeEmpty(bc::Tileset::Type tileset)
    {
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::EnemyProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Enemies));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Items));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::PlayerProjectiles, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Enemies, CollisionGroup::PlayerProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::LevelElements, CollisionGroup::LevelElements));

        se::Engine::setActiveCamera(this->camera);

        this->entities.resize(7);
        this->hitboxes.resize(7);

        //spawn player
        std::vector<IModifier*> modifiers;
        modifiers.push_back(new PlayerModifier(&this->entities));
        Entity player(se::Content::getSprite("TestPlayer"), modifiers);
        player.hitbox = se::Content::getHitbox("TestPlayer");
        player.id = 0;
        player.getSprite().setPosition(se::Vector2(0, -200));
        player.init();
        this->hitboxes[CollisionGroup::Players].push_back(player.getSprite().getRect());
        this->entities[CollisionGroup::Players].push_back(player);

        this->medicineBox = MedicineBox((PlayerModifier*)modifiers[0]);

        Spawner::initialize(&this->hitboxes, &this->entities);

        this->totalElapsedTime = 0.0f;
        this->currentScrollKey = 0;

        ScrollKey key;
        key.time = 0.0f;
        key.speed = 100.0f;
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

        this->createBackgrounds(tileset, 24);
    }


    void Level::initialize(std::string source)
    {
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::EnemyProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Enemies));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::Items));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Players, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::PlayerProjectiles, CollisionGroup::LevelElements));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::Enemies, CollisionGroup::PlayerProjectiles));
        this->collisionConfigs.push_back(std::pair<CollisionGroup::Type, CollisionGroup::Type>(CollisionGroup::LevelElements, CollisionGroup::LevelElements));
        
        se::Engine::setActiveCamera(this->camera);

        this->entities.resize(7);
        this->hitboxes.resize(7);

        //spawn player
        std::vector<IModifier*> modifiers;
        modifiers.push_back(new PlayerModifier(&this->entities));
        Entity player(se::Content::getSprite("TestPlayer"), modifiers);
        player.hitbox = se::Content::getHitbox("TestPlayer");
        player.id = 0;
        player.getSprite().setPosition(se::Vector2(0, -200));
        player.init();
        this->hitboxes[CollisionGroup::Players].push_back(player.getSprite().getRect());
        this->entities[CollisionGroup::Players].push_back(player);

        this->medicineBox = MedicineBox((PlayerModifier*)modifiers[0]);

        Spawner::initialize(&this->hitboxes, &this->entities, source);

        this->totalElapsedTime = 0.0f;
        this->currentScrollKey = 0;

        std::string path = "../Content/Levels/" + source + "/Scrolling.txt";
        FILE* file = fopen(path.c_str(), "r");

        ScrollKey key;
        float time, speed;
        while (fscanf(file, "%f %f", &time, &speed) != EOF)
        {
            key.time = time;
            key.speed = speed;
            this->scrollSpeeds.push_back(key);
        }

        fclose(file);

        this->backgroundSpeeds.push_back(1.0f);
        this->backgroundSpeeds.push_back(0.8f);
        this->backgroundSpeeds.push_back(0.6f);
        this->backgroundSpeeds.push_back(0.4f);

        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());
        this->backgroundSprites.push_back(std::vector<se::Sprite>());

        path = "../Content/Levels/" + source + "/Background.txt";
        file = fopen(path.c_str(), "r");

        char tileset[32];
        int length;
        fscanf(file, "Tileset %s\nLength %d", tileset, &length);

        fclose(file);

        Tileset::Type tilesettype;
        if (strcmp(tileset, "Flesh") == 0)
        {
            tilesettype = Tileset::Flesh;
        }
        else if (strcmp(tileset, "Slime") == 0)
        {
            tilesettype = Tileset::Slime;
        }
        else if (strcmp(tileset, "Pus") == 0)
        {
            tilesettype = Tileset::Pus;
        }
        else if (strcmp(tileset, "Nerves") == 0)
        {
            tilesettype = Tileset::Nerves;
        }

        this->createBackgrounds(tilesettype, length);
    }


    void Level::update(float elapsedTime)
    {
        elapsedTime *= this->medicineBox.gamespeed;
        if (se::Input::getActionValue(bg::InputAction::FasterCheat))
        {
            elapsedTime *= 5.0f;
            this->entities[CollisionGroup::Players][0].health = 1.0f;
            this->entities[CollisionGroup::Players][0].dead = false;
        }

        std::vector<Entity>::iterator entIter;
        std::vector<Entity>::iterator entEnd;
        std::vector<se::Rectangle>::iterator rectIter;

        //updating
        for (unsigned int i = 0; i < this->entities.size(); ++i)
        {
            for (unsigned int j = 0; j < this->entities[i].size(); ++j)
            {
                this->entities[i][j].update(elapsedTime);
                this->hitboxes[i][j] = this->entities[i][j].getHitRect();
                if (this->entities[i][j].dead)
                    Spawner::kill(this->entities[i][j], (CollisionGroup::Type)i);
            }
        }

        //collision detection
        for (unsigned int i = 0; i < this->collisionConfigs.size(); ++i)
        {
            for (unsigned int j = 0; j < this->hitboxes[this->collisionConfigs[i].first].size(); ++j)
            {
                for (unsigned int k = 0; k < this->hitboxes[this->collisionConfigs[i].second].size(); ++k)
                {
                    if (this->collisionConfigs[i].first == this->collisionConfigs[i].second && j == k)
                        break;

                    if (this->hitboxes[this->collisionConfigs[i].first][j].overlap(this->hitboxes[this->collisionConfigs[i].second][k]))
                    {
                        se::Vector2 projectionNormal;
                        float projectionScalar;
                        if (this->entities[this->collisionConfigs[i].first][j].getHitbox().overlap(this->entities[this->collisionConfigs[i].second][k].getHitbox(), &projectionNormal, &projectionScalar))
                        {
                            this->entities[this->collisionConfigs[i].first][j].hit(&this->entities[this->collisionConfigs[i].second][k], this->collisionConfigs[i].second, projectionNormal, -projectionScalar);
                            this->entities[this->collisionConfigs[i].second][k].hit(&this->entities[this->collisionConfigs[i].first][j], this->collisionConfigs[i].first, projectionNormal, projectionScalar);
                        }
                    }
                }
            }
        }

        this->medicineBox.update(elapsedTime);

        Spawner::update(elapsedTime);

        printf("\rScore: %u Multiplier: %f Infection: %f%%            ", GameData::score, GameData::multiplier, GameData::humanInfection * 100.0f);

        //background scrolling
        this->totalElapsedTime += elapsedTime;

        if (this->entities[CollisionGroup::Players].size() > 0)
            this->camera.setPosition(se::Vector2(this->entities[CollisionGroup::Players][0].getSprite().getPosition().x / (se::Engine::getSettings().renderResolutionWidth / 2), 0.0f));

        float currentScrollSpeed = 0.0f;
        if (this->currentScrollKey + 1 < this->scrollSpeeds.size())
        {
            float factor = (this->totalElapsedTime - this->scrollSpeeds[this->currentScrollKey].time) / (this->scrollSpeeds[this->currentScrollKey + 1].time - this->scrollSpeeds[this->currentScrollKey].time);
            currentScrollSpeed = se::Math::Lerp(this->scrollSpeeds[this->currentScrollKey].speed, this->scrollSpeeds[this->currentScrollKey + 1].speed, factor);

            if (this->totalElapsedTime > this->scrollSpeeds[this->currentScrollKey + 1].time)
                ++this->currentScrollKey;
        }

        for (unsigned int i = 0; i < this->backgroundSprites.size(); ++i)
        {
            for (unsigned int j = 0; j < this->backgroundSprites[i].size(); ++j)
            {
                this->backgroundSprites[i][j].move(se::Vector2((this->camera.getActualPosition().x - this->lastCameraPos.x) * (1 - this->backgroundSpeeds[i]) * (se::Engine::getSettings().renderResolutionWidth / 2), currentScrollSpeed * -this->backgroundSpeeds[i] * elapsedTime));
            }
        }

        this->lastCameraPos = this->camera.getActualPosition();

        for (unsigned int i = 0; i < this->entities[CollisionGroup::LevelElements].size(); ++i)
        {
            this->entities[CollisionGroup::LevelElements][i].getSprite().move(se::Vector2(0.0f, -currentScrollSpeed * elapsedTime));
        }

        this->camera.update(elapsedTime);
    }


    void Level::draw()
    {
        for (unsigned int i = 0; i < this->backgroundSprites.size(); ++i)
        {
            for (unsigned int j = 0; j < this->backgroundSprites[i].size(); ++j)
            {
                se::Engine::draw(this->backgroundSprites[i][j]);
            }
        }

        for (unsigned int i = 0; i < this->entities.size(); ++i)
        {
            for (unsigned int j = 0; j < this->entities[i].size(); ++j)
            {
                /*se::Rectangle textRect = this->entities[i][j].getSprite().getRect();

                se::Sprite line = se::Content::getSprite("Pixel");

                line.setPosition(se::Vector2(textRect.left + (textRect.right - textRect.left) / 2.0f, textRect.top));
                line.setScale(se::Vector2((textRect.right - textRect.left), 1.0f));
                line.setRotation(0.0f);
                se::Engine::draw(line);

                line.setPosition(se::Vector2(textRect.right, textRect.top + (textRect.bottom - textRect.top) / 2.0f));
                line.setScale(se::Vector2((textRect.bottom - textRect.top), 1.0f));
                line.setRotation(90.0f);
                se::Engine::draw(line);

                line.setPosition(se::Vector2(textRect.left + (textRect.right - textRect.left) / 2.0f, textRect.bottom));
                line.setScale(se::Vector2((textRect.right - textRect.left), 1.0f));
                line.setRotation(0.0f);
                se::Engine::draw(line);

                line.setPosition(se::Vector2(textRect.left, textRect.top + (textRect.bottom - textRect.top) / 2.0f));
                line.setScale(se::Vector2((textRect.bottom - textRect.top), 1.0f));
                line.setRotation(90.0f);
                se::Engine::draw(line);*/

                se::Engine::draw(this->entities[i][j].getSprite());
            }
        }
    }
}