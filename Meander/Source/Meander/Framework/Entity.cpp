#include "pch.h"
#include "Entity.h"

namespace Meander
{
    uint32_t Entity::s_UidFactory = 0;

    void Entity::Enable()
    {
        if (bIsEnabled)
            return;

        bIsEnabled = true;
    }

    void Entity::Disable()
    {
        if (!bIsEnabled)
            return;

        bIsEnabled = false;
    }

    void Entity::Destroy()
    {
        Disable();
        bIsDestroyed = true;
    }

    void Entity::SetName(const char* name)
    {
        // Create a default name if passing a nullptr
        // or if the name is just a null-terminator
        if (name == nullptr || (strlen(name) == 1 && name[0] == '\0'))
        {
            sprintf_s(m_Name, ENTITY_NAME_LENGTH, "Entity %i", s_UidFactory);
            return;
        }

        // Ensure we're not exceeding length
        if (strlen(name) > ENTITY_NAME_LENGTH)
        {
            MN_WARN("Entity name \"{}\" exceeds the expected length.", name);
            return;
        }

        sprintf_s(m_Name, ENTITY_NAME_LENGTH, name);
    }
}