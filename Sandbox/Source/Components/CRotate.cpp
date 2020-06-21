#include "CRotate.h"
#include <Meander/Framework/Entity.h>
#include <Meander/Math/Random.h>

namespace Sandbox
{
    void CRotate::Awake()
    {
        Meander::Random RNG(GetEntity()->GetUniqueId() * ((float)time(0) + 1.f));
        Axis = RNG.Axis();
    }

    void CRotate::Tick(float deltaTime)
    {
        GetEntity()->GetTransform().Rotate(glm::radians(DegreesPerSecond) * deltaTime, Axis);
    }
}