#include "pch.h"
#include "Component.h"
#include "Meander/Framework/Actor.h"

namespace Meander
{
    Component::~Component()
    {
        // Ensure we remove ourselves from owner if we're destructed
        // without their instigation
        if (m_Owner == nullptr)
            return;

        if (Actor* actor = static_cast<Actor*>(m_Owner))
            actor->Unregister(this);
    }
}
