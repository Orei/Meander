#pragma once
#include <Meander/Framework/Components/Component.h>
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
        
    public:
        inline virtual const ComponentType& GetType() const override
        {
            return StaticType();
        }

        static const ComponentType& StaticType()
        {
            static ComponentType type({ "Rotate" });
            return type;
        }
    };
}
