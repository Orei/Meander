﻿#pragma once
#include "Meander/Framework/Component.h"

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

        COMPONENT_TYPE("StaticMesh");

    private:
        Mesh* m_Mesh = nullptr;
        Material* m_Material = nullptr;
    };
}
