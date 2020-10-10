#include "MeshActor.h"
#include <Meander/Framework/Components/StaticMesh.h>

namespace Sandbox
{
    MeshActor::MeshActor(const char* name)
        : Actor(name)
    {
        m_StaticMesh = Create<Meander::CStaticMesh>();
    }
}