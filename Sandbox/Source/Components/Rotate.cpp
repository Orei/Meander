#include "Rotate.h"
#include <Meander/Framework/Actor.h>
#include <Meander/Math/Random.h>

namespace Sandbox
{
    void CRotate::Awake()
    {
        Meander::Random RNG;
        Axis = RNG.Axis();
    }

    void CRotate::Tick(float deltaTime)
    {
        GetOwner()->GetTransform().Rotate(glm::radians(DegreesPerSecond) * deltaTime, Axis);
    }
}