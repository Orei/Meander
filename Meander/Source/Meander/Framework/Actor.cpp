﻿#include "pch.h"
#include "Actor.h"
#include "Component.h"

namespace Meander
{
    Actor::~Actor()
    {
        // TODO: Should switch to smart pointers at some point probably
        for (auto it = m_Components.begin(); it != m_Components.end(); it++)
            delete it->second;

        m_Components.clear();
    }

    void Actor::Tick(float deltaTime)
    {
        for (auto it = m_Components.begin(); it != m_Components.end(); it++)
        {
            auto& component = it->second;
            component->Tick(deltaTime);
        }
    }

    void Actor::Register(Component* component)
    {
        // Add to our list of components
        const char* type = component->GetType();
        m_Components[type] = component;

        // Make component aware of it's owner
        component->SetOwner(this);
    }

    void Actor::Unregister(Component* component)
    {
        if (component == nullptr)
            return;
        
        // Get the static type
        const char* type = component->GetType();
        if (m_Components[type] != component)
            return;

        // Remove our reference to it
        m_Components[type] = nullptr;

        // Make component aware it's orphaned
        component->SetOwner(nullptr);
    }
}
