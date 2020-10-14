#pragma once
#include <Meander/Framework/Component.h>
#include <Meander/Common.h>
#include <glm/vec3.hpp>

namespace Sandbox
{
    class CRotate : public Meander::Component
    {
    public:
        glm::vec3 Axis = WORLD_UP;
        float DegreesPerSecond = 45.f;
        
        virtual void Awake() override;
        virtual void Tick(float deltaTime) override;

        COMPONENT_TYPE("Rotate")
    };
}
