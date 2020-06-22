#pragma once
#include "Meander/Framework/Components/ComponentType.h"
#include "Meander/Transform.h"
#include <unordered_map>
#include <string>

#define ENTITY_NAME_LENGTH 32

namespace Meander
{
    class World;
    class Component;
    
    class Entity
    {
    public:
        Entity(const char* name = nullptr)
            : m_UniqueId(s_UidFactory++), m_Name(new char[ENTITY_NAME_LENGTH])
        {
            SetName(name);
        }

        virtual ~Entity()
        {
            delete m_Name;
        }

        virtual void Awake();
        virtual void Tick(float deltaTime);

        void Enable();
        void Disable();
        void Destroy();

        void SetWorld(World* world) { m_World = world; }
        void SetName(const char* name);
        void SetTransform(const Transform& transform) { m_Transform = transform; }

        template<typename T>
        T* Create()
        {
            T* component = new T();
            const ComponentType& type = T::StaticType();
            m_Components[type.Name] = component;
            Register(component);
            component->Awake();
            return component;
        }
        
        template<typename T>
        T* Get()
        {
            const ComponentType& type = T::StaticType();
            
            auto it = m_Components.find(type.Name);
            if (it == m_Components.end())
                return nullptr;

            return static_cast<T*>(it->second);
        }

        inline const char* GetName() const { return m_Name; }
        inline unsigned int GetUniqueId() const { return m_UniqueId; }
        inline World* GetWorld() const { return m_World; }
        inline Transform& GetTransform() { return m_Transform; }
        inline bool IsEnabled() const { return bIsEnabled; }
        inline bool IsDestroyed() const { return bIsDestroyed; }
        
        const std::unordered_map<std::string, Component*>& GetComponents() const { return m_Components; }

    private:
        unsigned int m_UniqueId = 0;
        char* m_Name = nullptr;
        World* m_World = nullptr;
        Transform m_Transform = {};
        bool bIsEnabled = true;
        bool bIsDestroyed = false;
        std::unordered_map<std::string, Component*> m_Components;

        void Register(Component* component);

        static unsigned int s_UidFactory;
    };
}
