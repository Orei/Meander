﻿#pragma once
#include "Meander/Framework/Entity.h"

#define COMPONENT_TYPE(type) static const char* GetStaticType() { return type; } \
    virtual const char* GetType() const override { return GetStaticType(); }

namespace Meander
{
    class Actor;
    
    class Component : public Entity
    {
    public:
        Component(const char* name = nullptr) : Entity(name) {}
        virtual ~Component();

        virtual void Awake() { }
        virtual void Tick(float deltaTime) { }

        virtual Actor* GetOwner() const { return m_Owner; }
        virtual const char* GetType() const = 0;

    protected:
        Actor* m_Owner = nullptr;

    private:
        void SetOwner(Actor* Actor) { m_Owner = Actor; }

        // TODO: Allows private access for Actor to set parent of this component, might be a better way to do this
        friend Actor;
    };
}
