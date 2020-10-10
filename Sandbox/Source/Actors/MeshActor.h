#pragma once
#include "Meander/Framework/Actor.h"

namespace Meander
{
    class CStaticMesh;
}

namespace Sandbox
{    
    class MeshActor : public Meander::Actor
    {
    public:
        MeshActor(const char* name = nullptr);

        inline Meander::CStaticMesh* GetStaticMesh() const { return m_StaticMesh; }
        
    private:
        Meander::CStaticMesh* m_StaticMesh = nullptr;
    };
}
