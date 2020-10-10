#pragma once
#include <vector>

namespace Meander
{
    class Actor;
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
            // TODO: Ensure T is actually actor
            T* actor = new T(name);
            actor->SetWorld(this);
            m_Actors.push_back(actor);
            actor->Awake();
            return actor;
        }
        
        template<typename T>
        T* Spawn(const char* name, const Transform& transform)
        {
            // TODO: Ensure T is actually actor
            T* actor = new T(name);
            actor->SetWorld(this);
            actor->SetTransform(transform);
            m_Actors.push_back(actor);
            actor->Awake();
            return actor;
        }

        std::vector<Actor*> GetActors() const { return m_Actors; }
        int NumEntities() const { return (int)m_Actors.size(); }

        // Angelscript requirements.
        inline void AddReference() { }
        inline void Release() { }

    private:
        std::vector<Actor*> m_Actors;
    };
}
