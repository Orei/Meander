#include "pch.h"
#include "Entity.h"
#include "Components/Component.h"

namespace Meander
{
    unsigned int Entity::s_UidFactory = 0;

    void Entity::Awake()
    {
        for (const auto& component : m_Components)
            ((Component*)component.second)->Awake();
    }

    void Entity::Tick(float deltaTime)
    {
        for (const auto& component : m_Components)
            ((Component*)component.second)->Tick(deltaTime);
    }

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
        // Default name if nullptr, this can't exceed 32 characters
        if (name == nullptr)
        {
            sprintf_s(m_Name, ENTITY_NAME_LENGTH, "Node %i", s_UidFactory);
            return;
        }

        // Ensure we're not exceeding length
        if (strlen(name) > ENTITY_NAME_LENGTH)
        {
            MN_WARN("Scene Node name exceeds the expected length.");
            return;
        }

        sprintf_s(m_Name, ENTITY_NAME_LENGTH, name);
    }

    void Entity::Register(Component* component)
    {
        component->SetEntity(this);
    }
}