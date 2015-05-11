#include "Spawner.h"

#include "Other\tinydir.h"
#include "AnimatedSprite.h"
#include "Content.h"
#include "EnemyModifier.h"
#include "HitMarkerModifier.h"

namespace bc
{
    std::vector<float> Spawner::spawnTimes = std::vector<float>();
    std::vector<Spawner::Spawn> Spawner::timedSpawns = std::vector<Spawner::Spawn>();
    std::vector<Spawner::Spawn> Spawner::immediateSpawns = std::vector<Spawner::Spawn>();
    float Spawner::totalElapsedTime = 0.0f;
    std::vector<std::vector<se::Rectangle>>* Spawner::hitboxes = 0;
    std::vector<std::vector<bc::Entity>>* Spawner::entities = 0;
    int Spawner::nextSpawn = 0;


    Entity Spawner::createEnemy(std::string name)
    {
        Entity result;

        if (name == "Virus")
        {
            result.dead = false;
            result.health = 500.0f;
            result.maxHealth = 500.0f;
            std::vector<IModifier*> modifiers;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.3f);
            sprite.addAnimation("Death");
            sprite.setSpeed("Death", 0.1f);
            sprite.addSprite("Idle", se::Content::getSprite("Virus1"));
            sprite.addSprite("Idle", se::Content::getSprite("Virus2"));
            sprite.addSprite("Idle", se::Content::getSprite("Virus3"));
            sprite.addSprite("Idle", se::Content::getSprite("Virus4"));
            sprite.addSprite("Death", se::Content::getSprite("VirusDie1"));
            sprite.addSprite("Death", se::Content::getSprite("VirusDie2"));
            sprite.addSprite("Death", se::Content::getSprite("VirusDie3"));
            sprite.addSprite("Death", se::Content::getSprite("VirusDie4"));
            sprite.addSprite("Death", se::Content::getSprite("VirusDie5"));
            sprite.setScale(se::Vector2(1.5f, 1.5f));
            modifiers.push_back(new EnemyModifier(sprite));
            modifiers.push_back(new HitMarkerModifier());
            result.modifiers = modifiers;
            result.sprite = se::Content::getSprite("Virus1");
        }

        return result;
    }


    void Spawner::initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities, std::string levelName)
    {
        Spawner::hitboxes = hitboxes;
        Spawner::entities = entities;

        std::string filePath = "../Content/Levels/" + levelName + "/Enemies.txt";

        FILE* file = fopen(filePath.c_str(), "r");

        char enemyName[256];
        float time, xPos, yPos;
        while (fscanf(file, "%s %f %f %f", enemyName, &time, &xPos, &yPos) != EOF)
        {
            Spawner::spawnTimes.push_back(time);
            Spawn spawn;
            spawn.collisionGroup = CollisionGroup::Enemies;
            spawn.entity = Spawner::createEnemy(enemyName);
            spawn.position = se::Vector2(xPos, yPos);
            Spawner::timedSpawns.push_back(spawn);
        }

        fclose(file);


        filePath = "../Content/Levels/" + levelName + "/Walls.txt";

        file = fopen(filePath.c_str(), "r");

        char tileName[256];
        while (fscanf(file, "%s %f %f", tileName, &xPos, &yPos) != EOF)
        {
            Spawn spawn;
            spawn.collisionGroup = CollisionGroup::LevelElements;
            spawn.entity = Entity(se::Content::getSprite(tileName), std::vector<IModifier*>());
            spawn.position = se::Vector2(xPos, yPos);
            Spawner::immediateSpawns.push_back(spawn);
        }

        fclose(file);

        (*Spawner::entities)[CollisionGroup::Enemies].reserve(Spawner::timedSpawns.size());
        (*Spawner::hitboxes)[CollisionGroup::Enemies].reserve(Spawner::timedSpawns.size());
    }


    void Spawner::update(float elapsedTime)
    {
        Spawner::totalElapsedTime += elapsedTime;

        unsigned int id;

        while (Spawner::nextSpawn < Spawner::spawnTimes.size() && Spawner::totalElapsedTime >= Spawner::spawnTimes[Spawner::nextSpawn])
        {
            Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().setPosition(Spawner::timedSpawns[Spawner::nextSpawn].position);
            (*Spawner::hitboxes)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity);
            ++Spawner::nextSpawn;
        }

        for (int i = 0; i < Spawner::immediateSpawns.size(); ++i)
        {
            Spawner::immediateSpawns[i].entity.getSprite().setPosition(Spawner::immediateSpawns[i].position);
            (*Spawner::hitboxes)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity);
        }

        Spawner::immediateSpawns.clear();
    }


    void Spawner::spawn(se::Vector2 position, Entity entity, CollisionGroup::Type collisionGroup)
    {
        Spawner::Spawn spawn;
        spawn.position = position;
        spawn.entity = entity;
        spawn.collisionGroup = collisionGroup;

        Spawner::immediateSpawns.push_back(spawn);
    }
}