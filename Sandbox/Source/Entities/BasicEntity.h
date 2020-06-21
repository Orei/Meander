#pragma once
#include <Meander/Framework/Entity.h>

namespace Meander
{
    class CStaticMesh;
}

namespace Sandbox
{    
    class BasicEntity : public Meander::Entity
    {
    public:
        BasicEntity(const char* name = nullptr);

        inline Meander::CStaticMesh* GetMesh() const { return StaticMesh; }
        
    private:
        Meander::CStaticMesh* StaticMesh = nullptr;
    };
}
