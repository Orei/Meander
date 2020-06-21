#pragma once
#include "ComponentType.h"

namespace Meander
{
    class Entity;
        
    class Component
    {
    public:
        virtual ~Component() {}

        virtual void Awake() { }
        virtual void Tick(float deltaTime) { }

        virtual Entity* GetEntity() const { return m_Entity; }
        virtual const ComponentType& GetType() const = 0;

    protected:
        Entity* m_Entity = nullptr;

    private:
        void SetEntity(Entity* entity) { m_Entity = entity; }

        // TODO: Allows private access for Entity to set parent, find a good way to do this
        friend Entity;
    };
}
