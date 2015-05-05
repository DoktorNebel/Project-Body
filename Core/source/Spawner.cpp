#include "Spawner.h"

namespace bc
{
    std::vector<float> Spawner::spawnTimes = std::vector<float>();
    std::vector<Spawner::Spawn> Spawner::timedSpawns = std::vector<Spawner::Spawn>();
    std::vector<Spawner::Spawn> Spawner::immediateSpawns = std::vector<Spawner::Spawn>();
    float Spawner::totalElapsedTime = 0.0f;
    std::vector<std::vector<se::Rectangle>>* Spawner::hitboxes = 0;
    std::vector<std::vector<bc::Entity>>* Spawner::entities = 0;


    void Spawner::initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities)
    {
        Spawner::hitboxes = hitboxes;
        Spawner::entities = entities;
    }


    void Spawner::update(float elapsedTime)
    {
        Spawner::totalElapsedTime += elapsedTime;

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