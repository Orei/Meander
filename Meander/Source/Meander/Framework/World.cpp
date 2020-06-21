#include "pch.h"
#include "World.h"
#include "Entity.h"

namespace Meander
{
    World::~World()
    {
        for (auto& entity : m_Entities)
            delete entity;

        m_Entities.clear();
    }

    void World::Tick(float deltaTime)
    {
        for (int i = m_Entities.size() - 1; i >= 0; --i)
        {
            const auto entity = m_Entities[i];

            if (entity->IsDestroyed())
            {
                m_Entities.erase(m_Entities.begin() + i);
                delete entity;
                return;
            }

            if (entity->IsEnabled())
                entity->Tick(deltaTime);
        }
    }
}