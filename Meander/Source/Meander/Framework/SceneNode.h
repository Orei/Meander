#pragma once
#include "Meander/Common.h"
#include "Meander/Transform.h"

namespace Meander
{
	class Mesh;
	class Material;

	class SceneNode
	{
	public:
		SceneNode()
			: m_UniqueId(s_UidFactory++)
		{
			m_Name = new char[32];
			sprintf_s(m_Name, 32, "Node %i", m_UniqueId);
		}

		void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
		void SetMaterial(Material* material) { m_Material = material; }

		Transform& GetTransform() { return m_Transform; }
		Mesh* GetMesh() const { return m_Mesh; }
		Material* GetMaterial() const { return m_Material; }

		unsigned int GetUniqueId() const { return m_UniqueId; }
		const char* GetName() const { return m_Name; }

	private:
		unsigned int m_UniqueId = 0;
		char* m_Name = nullptr;
		Transform m_Transform = {};
		Mesh* m_Mesh = nullptr;
		Material* m_Material = nullptr;

		static unsigned int s_UidFactory;
	};
}