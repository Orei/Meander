#pragma once
#include "Meander/Math/Transform.h"

#define ENTITY_NAME_LENGTH 32

namespace Meander
{
    class World;

    // Base class for all game objects.
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

        virtual void Awake() {}
        virtual void Tick(float deltaTime) {}

        void Enable();
        void Disable();
        void Destroy();

        void SetWorld(World* world) { m_World = world; }
        void SetName(const char* name);
        void SetTransform(const Transform& transform) { m_Transform = transform; }

        inline const char* GetName() const { return m_Name; }
        inline unsigned int GetUniqueId() const { return m_UniqueId; }
        inline World* GetWorld() const { return m_World; }
        inline Transform& GetTransform() { return m_Transform; }
        inline bool IsEnabled() const { return bIsEnabled; }
        inline bool IsDestroyed() const { return bIsDestroyed; }

        // Angelscript requirements.
        inline void AddReference() { }
        inline void Release() { }

    private:
        uint32_t m_UniqueId = 0;
        char* m_Name = nullptr;
        World* m_World = nullptr;
        Transform m_Transform = {};
        bool bIsEnabled = true;
        bool bIsDestroyed = false;

        static uint32_t s_UidFactory;
    };
}
