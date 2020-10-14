#pragma once
#include "Entity.h"
#include <unordered_map>

namespace Meander
{
    class Component;

    class Actor : public Entity
    {
    public:
        Actor(const char* name = nullptr) : Entity(name) {}
        virtual ~Actor();

        template<typename T>
        T* Create()
        {
            T* component = new T();
            Register(component);
            // TODO: When should Awake be called? Before first tick, when created, when "ready to use"?
            component->Awake();
            return component;
        }
            
        template<typename T>
        T* Get()
        {
            const char* type = T::GetStaticType();
                
            auto it = m_Components.find(type);
            if (it == m_Components.end())
                return nullptr;

            return static_cast<T*>(it->second);
        }
                
        const std::unordered_map<const char*, Component*>& GetComponents() const { return m_Components; }

    private:
        std::unordered_map<const char*, Component*> m_Components;
        
        void Register(Component* component);
        void Unregister(Component* component);

        // TODO: This could be a poor idea, but we need to let the actor know when a component is removed.
        friend class Component;
    };
}
