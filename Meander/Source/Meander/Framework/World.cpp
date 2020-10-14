#include "pch.h"
#include "World.h"

#include "Actor.h"
#include "Entity.h"

namespace Meander
{
    World::~World()
    {
        for (auto& actor : m_Actors)
            delete actor;

        m_Actors.clear();
    }

    void World::Tick(float deltaTime)
    {
        for (size_t i = m_Actors.size() - 1; i > 0; --i)
        {
            auto& actor = m_Actors[i];

            // TODO: This should probably be handled elsewhere
            if (actor->IsDestroyed())
            {
                m_Actors.erase(m_Actors.begin() + i);
                delete actor;
                continue;
            }

            if (actor->IsEnabled())
                actor->Tick(deltaTime);
        }
    }
}