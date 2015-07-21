#include "Spawner.h"

#include "Other\tinydir.h"
#include "AnimatedSprite.h"
#include "Content.h"
#include "EnemyModifier.h"
#include "HitMarkerModifier.h"
#include "HomingMovementModifier.h"
#include "BoogerModifier.h"
#include "ShooterModifier.h"
#include "BigVirusModifier.h"
#include "WormElementModifier.h"
#include "Other\tinydir.h"

namespace bc
{
    std::vector<float> Spawner::spawnTimes = std::vector<float>();
    std::vector<Spawner::Spawn> Spawner::timedSpawns = std::vector<Spawner::Spawn>();
    std::vector<Spawner::Spawn> Spawner::immediateSpawns = std::vector<Spawner::Spawn>();
    float Spawner::totalElapsedTime = 0.0f;
    std::vector<std::vector<se::Rectangle>>* Spawner::hitboxes = 0;
    std::vector<std::vector<bc::Entity>>* Spawner::entities = 0;
    unsigned int Spawner::nextSpawn = 0;
    unsigned int Spawner::highestId = 1;
    std::vector<unsigned int> Spawner::freeIds = std::vector<unsigned int>();
    std::vector<Spawner::Spawn> Spawner::killList = std::vector<Spawner::Spawn>();
    std::vector<std::string> Spawner::movementPatternNames = std::vector<std::string>();
    std::vector<std::vector<MovementPatternModifier::Waypoint>> Spawner::movementPatterns = std::vector<std::vector<MovementPatternModifier::Waypoint>>();
    std::vector<std::string> Spawner::shotPatternNames = std::vector<std::string>();
    std::vector<ShootingModifier::ShotPattern> Spawner::shotPatterns = std::vector<ShootingModifier::ShotPattern>();
    std::vector<std::string> Spawner::animationNames = std::vector<std::string>();
    std::vector<se::AnimatedSprite> Spawner::animations = std::vector<se::AnimatedSprite>();
    std::vector<std::string> Spawner::bossPatternNames = std::vector<std::string>();
    std::vector<std::vector<BossModifier::Phase>> Spawner::bossPatterns = std::vector<std::vector<BossModifier::Phase>>();
    std::vector<float> Spawner::bossHealth = std::vector<float>();
    bool Spawner::bossAlive = false;


    Entity Spawner::createEnemy(std::string name, std::string movementPattern)
    {
        Entity result;
        std::vector<IModifier*> modifiers;

        unsigned int pos;
        if ((pos = std::find(Spawner::bossPatternNames.begin(), Spawner::bossPatternNames.end(), name) - Spawner::bossPatternNames.begin()) < Spawner::bossPatternNames.size())
        {
            result.dead = false;
            result.health = Spawner::bossHealth[pos];
            result.maxHealth = Spawner::bossHealth[pos];
            modifiers.push_back(new BossModifier(Spawner::bossPatterns[pos]));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite(name);
            result.hitbox = se::Content::getHitbox(name);
        }

        bool golden = false;
        ItemModifier::Effect::Type dropType;
        if ((pos = name.find("_Drop")) != std::string::npos)
        {
            golden = true;
            std::string drop = name.substr(pos, name.size());
            if (drop == "_DropNormal")
                dropType = ItemModifier::Effect::Normal;
            else if (drop == "_DropSplit")
                dropType = ItemModifier::Effect::Split;
            name = name.substr(0, pos);
        }

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
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            modifiers.push_back(new EnemyModifier(sprite, 2, 0.02f));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("Virus1");
            result.hitbox = se::Content::getHitbox("Virus1");
        }
        else if (name == "Big_Virus")
        {
            result.dead = false;
            result.health = 5.0f;
            result.maxHealth = 5.0f;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.3f);
            sprite.addSprite("Idle", se::Content::getSprite("V1"));
            sprite.addSprite("Idle", se::Content::getSprite("V2"));
            sprite.addSprite("Idle", se::Content::getSprite("V3"));
            sprite.addSprite("Idle", se::Content::getSprite("V4"));
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            modifiers.push_back(new EnemyModifier(sprite, 5, 0.02f));
            modifiers.push_back(new BigVirusModifier());
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("V1");
            result.hitbox = se::Content::getHitbox("V1");
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
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            modifiers.push_back(new EnemyModifier(sprite, 250, 0.05f));
            modifiers.push_back(new HitMarkerModifier());
            modifiers.push_back(new ShootingModifier(Spawner::shotPatterns[std::find(Spawner::shotPatternNames.begin(), Spawner::shotPatternNames.end(), "BigBug") - Spawner::shotPatternNames.begin()]));
            result.sprite = se::Content::getSprite("KillaBug1");
            result.hitbox = se::Content::getHitbox("KillaBug1");
        }
        else if (name == "Little_Bug")
        {
            result.dead = false;
            result.health = 20.0f;
            result.maxHealth = 20.0f;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.5f);
            sprite.addSprite("Idle", se::Content::getSprite("Kefer"));
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            modifiers.push_back(new EnemyModifier(sprite, 20, 0.02f));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("Kefer");
            result.hitbox = se::Content::getHitbox("Kefer");
        }
        else if (name == "Booger")
        {
            result.dead = false;
            result.health = 200.0f;
            result.maxHealth = 200.0f;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.5f);
            sprite.addSprite("Idle", se::Content::getSprite("Popel"));
            sprite.setScale(se::Vector2(1.5f, 1.5f));
            modifiers.push_back(new EnemyModifier(sprite, 200, 0.0f));
            modifiers.push_back(new BoogerModifier());
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("Popel");
            result.hitbox = se::Content::getHitbox("Popel");
        }
        else if (name == "Shooter")
        {
            result.dead = false;
            result.health = 100.0f;
            result.maxHealth = 100.0f;
            modifiers.push_back(new ShooterModifier(Spawner::entities));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("Shooter");
            result.sprite.scale(se::Vector2(1.0f, 1.0f));
            result.hitbox = se::Content::getHitbox("Shooter");
        }
        else if (name == "Neurax_Worm")
        {
            result.dead = false;
            result.health = 50.0f;
            result.maxHealth = 50.0f;
            se::AnimatedSprite sprite;
            sprite.addAnimation("Idle");
            sprite.setSpeed("Idle", 0.05f);
            sprite.addAnimation("Death");
            sprite.setSpeed("Death", 0.1f);
            sprite.addSprite("Idle", se::Content::getSprite("Neurax1"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax2"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax3"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax4"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax5"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax6"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax7"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax8"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax9"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax10"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax11"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax12"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax13"));
            sprite.addSprite("Idle", se::Content::getSprite("Neurax14"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_1"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_2"));
            sprite.addSprite("Death", se::Content::getSprite("Worm_Explosion_3"));
            sprite.setScale(se::Vector2(1.0f, 1.0f));
            sprite.setDepth(-1.0f);
            modifiers.push_back(new EnemyModifier(sprite, 50, 0.1f));
            modifiers.push_back(new WormElementModifier(true, 10, 0));
            modifiers.push_back(new HitMarkerModifier());
            result.sprite = se::Content::getSprite("Neurax1");
            result.hitbox = se::Content::getHitbox("Neurax1");
        }

        if (golden)
        {
            ((EnemyModifier*)modifiers[0])->golden = true;
            ((EnemyModifier*)modifiers[0])->dropType = dropType;
        }

        IModifier* movement = 0;
        if (movementPattern == "Seek_Player")
        {
            movement = new HomingMovementModifier(&(*Spawner::entities)[CollisionGroup::Players][0], 100.0f, false, 1.0f);
        }
        else if (movementPattern == "Seek_Player_Delayed")
        {
            movement = new HomingMovementModifier(&(*Spawner::entities)[CollisionGroup::Players][0], 100.0f, true, 1.0f);
        }
        else
        {
            unsigned int pos = std::find(Spawner::movementPatternNames.begin(), Spawner::movementPatternNames.end(), movementPattern) - Spawner::movementPatternNames.begin();
            if (pos < Spawner::movementPatternNames.size())
                movement = new MovementPatternModifier(Spawner::movementPatterns[pos], 0.0f, 1.0f, MovementPatternModifier::Style::Kill);
        }

        if (movement != 0)
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


    bool Spawner::getAnimation(std::string name, se::AnimatedSprite* outSprite)
    {
        unsigned int pos = std::find(Spawner::animationNames.begin(), Spawner::animationNames.end(), name) - Spawner::animationNames.begin();
        if (pos < Spawner::animationNames.size())
        {
            *outSprite = Spawner::animations[pos];
            return true;
        }
        return false;
    }


    ShootingModifier::ShotPattern Spawner::getShotPattern(std::string patternName)
    {
        int pos = std::find(Spawner::shotPatternNames.begin(), Spawner::shotPatternNames.end(), patternName) - Spawner::shotPatternNames.begin();
        return Spawner::shotPatterns[pos];
    }


    std::vector<MovementPatternModifier::Waypoint> Spawner::getMovementPattern(std::string patternName)
    {
        unsigned int pos = std::find(Spawner::movementPatternNames.begin(), Spawner::movementPatternNames.end(), patternName) - Spawner::movementPatternNames.begin();
        return pos < Spawner::movementPatterns.size() ? Spawner::movementPatterns[pos] : std::vector<MovementPatternModifier::Waypoint>();
    }


    void Spawner::initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities, std::string levelName)
    {
        Spawner::hitboxes = hitboxes;
        Spawner::entities = entities;

        //get movement pattern filenames
        std::vector<std::string> fileNames;
        tinydir_dir dir;
        tinydir_open_sorted(&dir, "../Content/Movement Patterns/");

        for (unsigned int i = 0; i < dir.n_files; ++i)
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
        for (unsigned int i = 0; i < fileNames.size(); ++i)
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

        //get shot pattern filenames
        fileNames.clear();
        tinydir_open_sorted(&dir, "../Content/Shot Patterns/");

        for (unsigned int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file tdfile;
            tinydir_readfile_n(&dir, &tdfile, i);

            if (!tdfile.is_dir && strcmp(tdfile.name, "Thumbs.db"))
            {
                fileNames.push_back(tdfile.name);
            }
        }

        tinydir_close(&dir);

        //get shot patterns
        char firstString[256];
        char secondString[256];
        float rotation;
        for (unsigned int i = 0; i < fileNames.size(); ++i)
        {
            filePath = "../Content/Shot Patterns/" + fileNames[i];

            file = fopen(filePath.c_str(), "r");

            char patternName[256];
            sscanf(fileNames[i].c_str(), "%[^.]", patternName);
            Spawner::shotPatternNames.push_back(patternName);
            ShootingModifier::ShotPattern shotPattern;
            int index = -1;
            while (fscanf(file, "%s %s %f %f", firstString, secondString, &speed, &rotation) != EOF)
            {
                if (strcmp(firstString, "Delay") == 0)
                {
                    float delay = (float)atof(secondString);
                    shotPattern.delays.push_back(delay);
                    shotPattern.shotSalvos.push_back(ShootingModifier::ShotPattern::Salvo());
                    ++index;
                }
                else
                {
                    shotPattern.shotSalvos[index].shotSpriteNames.push_back(firstString);
                    shotPattern.shotSalvos[index].shotMovementNames.push_back(secondString);
                    shotPattern.shotSalvos[index].speeds.push_back(speed);
                    shotPattern.shotSalvos[index].rotations.push_back(rotation);
                }
            }

            Spawner::shotPatterns.push_back(shotPattern);

            fclose(file);
        }

        //get boss pattern filenames
        fileNames.clear();
        tinydir_open_sorted(&dir, "../Content/Bosses/");

        for (unsigned int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file tdfile;
            tinydir_readfile_n(&dir, &tdfile, i);

            if (!tdfile.is_dir && strcmp(tdfile.name, "Thumbs.db"))
            {
                fileNames.push_back(tdfile.name);
            }
        }

        tinydir_close(&dir);

        //get boss patterns
        for (unsigned int i = 0; i < fileNames.size(); ++i)
        {
            char patternName[256];
            sscanf(fileNames[i].c_str(), "%[^.]", patternName);
            Spawner::bossPatternNames.push_back(patternName);

            filePath = "../Content/Bosses/" + fileNames[i];

            file = fopen(filePath.c_str(), "r");

            std::vector<BossModifier::Phase> phases;
            int currentPhase = -1;

            while (fscanf(file, "%s %[^\n]", firstString, secondString) != EOF)
            {
                if (strcmp(firstString, "Health") == 0)
                {
                    Spawner::bossHealth.push_back((float)atof(secondString));
                }

                if (strcmp(firstString, "Phase") == 0)
                {
                    BossModifier::Phase phase;
                    phase.startHealth = (float)atof(secondString);
                    phases.push_back(phase);
                    ++currentPhase;
                }

                if (strcmp(firstString, "Movement") == 0)
                {
                    char movementName[128];
                    char modeName[128];
                    if (sscanf(secondString, "%s %s", movementName, modeName))
                    {
                        phases[currentPhase].movementPattern = movementName;
                        if (strcmp(modeName, "Stay") == 0)
                            phases[currentPhase].movementType = MovementPatternModifier::Style::Stay;
                        else if (strcmp(modeName, "Kill") == 0)
                            phases[currentPhase].movementType = MovementPatternModifier::Style::Kill;
                        else if (strcmp(modeName, "Repeat") == 0)
                            phases[currentPhase].movementType = MovementPatternModifier::Style::Repeat;
                        else if (strcmp(modeName, "Reverse") == 0)
                            phases[currentPhase].movementType = MovementPatternModifier::Style::Reverse;
                    }
                }

                if (strcmp(firstString, "Shooting") == 0)
                {
                    phases[currentPhase].shotPattern = secondString;
                }

                if (strcmp(firstString, "Part") == 0)
                {
                    float spawnX, spawnY;
                    char spriteName[128];
                    char movementName[128];
                    char movementSpecial[128];
                    char shotPatternName[128];

                    if (sscanf(secondString, "%f %f %s %s %s %s", &spawnX, &spawnY, spriteName, movementName, movementSpecial, shotPatternName))
                    {
                        BossModifier::Phase::Part part;
                        part.spawnPosition = se::Vector2(spawnX, spawnY);
                        part.spriteName = spriteName;
                        part.movePatternName = movementName;
                        if (strcmp(movementSpecial, "NoRotate") == 0)
                            part.noRotate = true;
                        else
                            part.noRotate = false;
                        part.shotPatternName = shotPatternName;
                        phases[currentPhase].parts.push_back(part);
                    }
                }
            }

            Spawner::bossPatterns.push_back(phases);

            fclose(file);
        }


        if (levelName != "")
        {
            //get enemy spawns
            filePath = "../Content/Levels/" + levelName + "/Enemies.txt";

            file = fopen(filePath.c_str(), "r");

            char enemyName[256];
            char patternName[256];
            while (fscanf(file, "%s %s %f %f %f", enemyName, patternName, &time, &xPos, &yPos) != EOF)
            {
                Spawner::spawnTimes.push_back(time);
                Spawn spawn;
                spawn.collisionGroup = strcmp(enemyName, "Booger") == 0 || strcmp(enemyName, "Shooter") == 0 ? CollisionGroup::LevelElements : CollisionGroup::Enemies;
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
                spawn.entity.hitbox = se::Content::getHitbox(tileName);
                spawn.position = se::Vector2(xPos, yPos);
                Spawner::immediateSpawns.push_back(spawn);
            }

            fclose(file);
        }


        //create animations
        se::AnimatedSprite sprite;
        sprite.addAnimation("Idle");
        sprite.setSpeed("Idle", 0.2f);
        sprite.addSprite("Idle", se::Content::getSprite("EneElek0"));
        sprite.addSprite("Idle", se::Content::getSprite("EneElek1"));
        sprite.addSprite("Idle", se::Content::getSprite("EneElek2"));
        Spawner::animationNames.push_back("EneElek");
        Spawner::animations.push_back(sprite);



        (*Spawner::entities)[CollisionGroup::Enemies].reserve(Spawner::timedSpawns.size());
        (*Spawner::entities)[CollisionGroup::Particles].reserve(5000);
        (*Spawner::hitboxes)[CollisionGroup::Enemies].reserve(Spawner::timedSpawns.size());
    }


    void Spawner::update(float elapsedTime)
    {
        if (!Spawner::bossAlive)
            Spawner::totalElapsedTime += elapsedTime;

        while (Spawner::nextSpawn < Spawner::spawnTimes.size() && Spawner::totalElapsedTime >= Spawner::spawnTimes[Spawner::nextSpawn])
        {
            Spawner::timedSpawns[Spawner::nextSpawn].entity.id = Spawner::getFreeId();
            Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().setPosition(Spawner::timedSpawns[Spawner::nextSpawn].position);
            if (Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup == CollisionGroup::LevelElements)
                Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().setDepth(0.1f);
            Spawner::timedSpawns[Spawner::nextSpawn].entity.init();
            (*Spawner::hitboxes)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::timedSpawns[Spawner::nextSpawn].collisionGroup].push_back(Spawner::timedSpawns[Spawner::nextSpawn].entity);
            ++Spawner::nextSpawn;
        }
        
        for (unsigned int i = 0; i < Spawner::immediateSpawns.size(); ++i)
        {
            Spawner::immediateSpawns[i].entity.id = Spawner::getFreeId();
            Spawner::immediateSpawns[i].entity.getSprite().setPosition(Spawner::immediateSpawns[i].position);
            if (Spawner::immediateSpawns[i].collisionGroup == CollisionGroup::LevelElements)
                Spawner::immediateSpawns[i].entity.getSprite().setDepth(0.1f);
            Spawner::immediateSpawns[i].entity.init();
            (*Spawner::hitboxes)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity.getSprite().getRect());
            (*Spawner::entities)[Spawner::immediateSpawns[i].collisionGroup].push_back(Spawner::immediateSpawns[i].entity);
        }

        Spawner::immediateSpawns.clear();

        for (unsigned int i = 0; i < Spawner::killList.size(); ++i)
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


    void Spawner::spawn(se::Vector2 position, std::string spriteName, std::vector<IModifier*> modifiers, CollisionGroup::Type collisionGroup)
    {
        Spawner::Spawn spawn;
        spawn.position = position;
        spawn.entity = Entity(se::Content::getSprite(spriteName), modifiers);
        spawn.entity.hitbox = se::Content::getHitbox(spriteName);
        spawn.collisionGroup = collisionGroup;

        Spawner::immediateSpawns.push_back(spawn);
    }


    void Spawner::spawnEnemy(se::Vector2 position, std::string enemyName, std::string movePatternName)
    {
        Spawn spawn;
        spawn.collisionGroup = enemyName == "Booger" || enemyName == "Shooter" ? CollisionGroup::ScrollingEnemies : CollisionGroup::Enemies;
        spawn.entity = Spawner::createEnemy(enemyName, movePatternName);
        spawn.position = position;

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


    std::vector<Entity>* Spawner::getEntities(CollisionGroup::Type entityType)
    {
        return &(*Spawner::entities)[entityType];
    }
}