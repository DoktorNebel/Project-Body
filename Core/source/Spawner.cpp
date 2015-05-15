#include "Spawner.h"

#include "Other\tinydir.h"
#include "AnimatedSprite.h"
#include "Content.h"
#include "EnemyModifier.h"
#include "HitMarkerModifier.h"
#include "HomingMovementModifier.h"
#include "Other\tinydir.h"

namespace bc
{
    std::vector<float> Spawner::spawnTimes = std::vector<float>();
    std::vector<Spawner::Spawn> Spawner::timedSpawns = std::vector<Spawner::Spawn>();
    std::vector<Spawner::Spawn> Spawner::immediateSpawns = std::vector<Spawner::Spawn>();
    float Spawner::totalElapsedTime = 0.0f;
    std::vector<std::vector<se::Rectangle>>* Spawner::hitboxes = 0;
    std::vector<std::vector<bc::Entity>>* Spawner::entities = 0;
    int Spawner::nextSpawn = 0;
    unsigned int Spawner::highestId = 1;
    std::vector<unsigned int> Spawner::freeIds = std::vector<unsigned int>();
    std::vector<Spawner::Spawn> Spawner::killList = std::vector<Spawner::Spawn>();
    std::vector<std::string> Spawner::movementPatternNames = std::vector<std::string>();
    std::vector<std::vector<MovementPatternModifier::Waypoint>> Spawner::movementPatterns = std::vector<std::vector<MovementPatternModifier::Waypoint>>();


    Entity Spawner::createEnemy(std::string name, std::string movementPattern)
    {
        Entity result;
        std::vector<IModifier*> modifiers;

        if (name == "Virus")
        {
            result.dead = false;
            result.health = 1.0f;
            result.maxHealth = 1.0f;
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
            result.sprite = se::Content::getSprite("Virus1");
        }
        else if (name == "Bug")
        {
            result.dead = false;
            result.health = 250.0f;
            result.maxHealth = 250.0f;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.5f);
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug1"));
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug2"));
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug3"));
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug4"));
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug5"));
            sprite.addSprite("Idle", se::Content::getSprite("KillaBug6"));
            sprite.setScale(se::Vector2(2.0f, 2.0f));
            modifiers.push_back(new EnemyModifier(sprite));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("KillaBug1");
        }

        IModifier* movement;
        if (movementPattern == "Seek_Player")
        {
            movement = new HomingMovementModifier(&(*Spawner::entities)[CollisionGroup::Players][0], 100.0f);
        }
        else
        {
            int pos = std::find(Spawner::movementPatternNames.begin(), Spawner::movementPatternNames.end(), movementPattern) - Spawner::movementPatternNames.begin();
            movement = new MovementPatternModifier(pos < Spawner::movementPatternNames.size() ? Spawner::movementPatterns[pos] : std::vector<MovementPatternModifier::Waypoint>());
        }

        modifiers.push_back(movement);
        result.modifiers = modifiers;

        return result;
    }


    unsigned int Spawner::getFreeId()
    {
        unsigned int result;

        if (Spawner::freeIds.size() > 0)
        {
            result = Spawner::freeIds.back();
            Spawner::freeIds.pop_back();
        }
        else
        {
            result = ++Spawner::highestId;
        }

        return result;
    }


    void Spawner::initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities, std::string levelName)
    {
        Spawner::hitboxes = hitboxes;
        Spawner::entities = entities;

        //get movement pattern filenames
        std::vector<std::string> fileNames;
        tinydir_dir dir;
        tinydir_open_sorted(&dir, "../Content/Movement Patterns/");

        for (int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file tdfile;
            tinydir_readfile_n(&dir, &tdfile, i);

            if (!tdfile.is_dir && strcmp(tdfile.name, "Thumbs.db"))
            {
                fileNames.push_back(tdfile.name);
            }
        }

        tinydir_close(&dir);

        //get movement patterns
        std::string filePath;
        FILE* file;
        float time, xPos, yPos, speed, waitTime;
        char special[256];
        for (int i = 0; i < fileNames.size(); ++i)
        {
            filePath = "../Content/Movement Patterns/" + fileNames[i];

            file = fopen(filePath.c_str(), "r");

            char patternName[256];
            sscanf(fileNames[i].c_str(), "%[^.]", patternName);
            Spawner::movementPatternNames.push_back(patternName);
            std::vector<MovementPatternModifier::Waypoint> waypoints;
            int result;
            while ((result = fscanf(file, "%f %f %f %f %s", &xPos, &yPos, &speed, &waitTime, special)) != EOF)
            {
                MovementPatternModifier::Waypoint waypoint;
                waypoint.position = se::Vector2(xPos, yPos);
                waypoint.speed = speed;
                waypoint.waitTime = waitTime;
                if (result > 4)
                {
                    waypoint.controlPoint = !strcmp(special, "control");
                }
                waypoints.push_back(waypoint);
            }
            Spawner::movementPatterns.push_back(waypoints);

            fclose(file);
        }

        //get enemy spawns
        filePath = "../Content/Levels/" + levelName + "/Enemies.txt";

        file = fopen(filePath.c_str(), "r");

        char enemyName[256];
        char patternName[256];
        while (fscanf(file, "%s %s %f %f %f", enemyName, patternName, &time, &xPos, &yPos) != EOF)
        {
            Spawner::spawnTimes.push_back(time);
            Spawn spawn;
            spawn.collisionGroup = CollisionGroup::Enemies;
            spawn.entity = Spawner::createEnemy(enemyName, patternName);
            spawn.position = se::Vector2(xPos, yPos);
            Spawner::timedSpawns.push_back(spawn);
        }

        fclose(file);


        //get level walls
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
        (*Spawner::entities)[CollisionGroup::Particles].reserve(5000);
        (*Spawner::hitboxes)[CollisionGroup::Enemies].reserve(Spawner::timedSpawns.size());
    }


    void Spawner::update(float elapsedTime)
    {
        Spawner::totalElapsedTime += elapsedTime;

        unsigned int id;

        while (Spawner::nextSpawn < Spawner::spawnTimes.size() && Spawner::totalElapsedTime >= Spawner::spawnTimes[Spawner::nextSpawn])
        {
            Spawner::timedSpawns[Spawner::nextSpawn].entity.id = Spawner::getFreeId();
            Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().setPosition(Spawner::timedSpawns[Spawner::nextSpawn].position);
            Spawner::timedSpawns[Spawner::nextSpawn].entity.init();
            (*Spawner::hitboxes)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity);
            ++Spawner::nextSpawn;
        }

        for (int i = 0; i < Spawner::immediateSpawns.size(); ++i)
        {
            Spawner::immediateSpawns[i].entity.id = Spawner::getFreeId();
            Spawner::immediateSpawns[i].entity.getSprite().setPosition(Spawner::immediateSpawns[i].position);
            Spawner::immediateSpawns[i].entity.init();
            (*Spawner::hitboxes)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity);
        }

        Spawner::immediateSpawns.clear();

        for (int i = 0; i < Spawner::killList.size(); ++i)
        {
            Spawner::freeIds.push_back(Spawner::killList[i].entity.id);

            int pos = std::find((*Spawner::entities)[Spawner::killList[i].collisionGroup].begin(), (*Spawner::entities)[Spawner::killList[i].collisionGroup].end(), Spawner::killList[i].entity) - (*Spawner::entities)[Spawner::killList[i].collisionGroup].begin();

            (*Spawner::entities)[Spawner::killList[i].collisionGroup][pos].destroy();

            if (pos != (*Spawner::entities)[Spawner::killList[i].collisionGroup].size() - 1)
            {
                (*Spawner::entities)[Spawner::killList[i].collisionGroup][pos] = std::move((*Spawner::entities)[Spawner::killList[i].collisionGroup].back());
            }
            (*Spawner::entities)[Spawner::killList[i].collisionGroup].pop_back();
            
            if (pos != (*Spawner::hitboxes)[Spawner::killList[i].collisionGroup].size() - 1)
            {
                (*Spawner::hitboxes)[Spawner::killList[i].collisionGroup][pos] = std::move((*Spawner::hitboxes)[Spawner::killList[i].collisionGroup].back());
            }
            (*Spawner::hitboxes)[Spawner::killList[i].collisionGroup].pop_back();
        }

        Spawner::killList.clear();
    }


    void Spawner::spawn(se::Vector2 position, Entity entity, CollisionGroup::Type collisionGroup)
    {
        Spawner::Spawn spawn;
        spawn.position = position;
        spawn.entity = entity;
        spawn.collisionGroup = collisionGroup;

        Spawner::immediateSpawns.push_back(spawn);
    }


    void Spawner::kill(Entity entity, CollisionGroup::Type collisionGroup)
    {
        Spawn spawn;
        spawn.position = se::Vector2();
        spawn.entity = entity;
        spawn.collisionGroup = collisionGroup;

        Spawner::killList.push_back(spawn);
    }
}