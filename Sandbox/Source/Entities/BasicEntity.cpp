#include "BasicEntity.h"
#include <Meander/Framework/Components/StaticMesh.h>

namespace Sandbox
{
    BasicEntity::BasicEntity(const char* name)
        : Entity(name)
    {
        StaticMesh = Create<Meander::CStaticMesh>();
    }
}