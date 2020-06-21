#pragma once
#include "Component.h"

namespace Meander
{
    class Material;
    class Mesh;

    class CStaticMesh : public Component
    {
    public:
        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        void SetMaterial(Material* material) { m_Material = material; }
        
        inline Mesh* GetMesh() const { return m_Mesh; }
        inline Material* GetMaterial() const { return m_Material; }

    private:
        Mesh* m_Mesh = nullptr;
        Material* m_Material = nullptr;

    public:
        inline virtual const ComponentType& GetType() const override
        {
            return StaticType();
        }
        
        static const ComponentType& StaticType()
        {
            static ComponentType type({ "Mesh" });
            return type;
        }
    };
}
