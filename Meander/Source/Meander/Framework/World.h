#pragma once
#include <vector>

namespace Meander
{
    class Transform;
    class Entity;
    
    class World
    {
    public:
        ~World();

        void Tick(float deltaTime);

        template<typename T>
        T* Spawn(const char* name)
        {
            T* entity = new T(name);
            entity->SetWorld(this);
            m_Entities.push_back(entity);
            entity->Awake();
            return entity;
        }
        
        template<typename T>
        T* Spawn(const char* name, const Transform& transform)
        {
            T* entity = new T(name);
            entity->SetWorld(this);
            entity->SetTransform(transform);
            m_Entities.push_back(entity);
            entity->Awake();
            return entity;
        }

        std::vector<Entity*> GetEntities() const { return m_Entities; }
        int NumEntities() const { return (int)m_Entities.size(); }

    private:
        std::vector<Entity*> m_Entities;
    };
}
