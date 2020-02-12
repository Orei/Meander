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

		void SetMesh(Shared<Mesh> mesh) { m_Mesh = mesh; }
		void SetMaterial(Shared<Material> material) { m_Material = material; }

		Transform& GetTransform() { return m_Transform; }
		const Shared<Mesh> GetMesh() const { return m_Mesh; }
		const Shared<Material> GetMaterial() const { return m_Material; }

		bool HasMesh() const { return m_Mesh != nullptr; }
		bool HasMaterial() const { return m_Material != nullptr; }

		unsigned int GetUniqueId() const { return m_UniqueId; }
		const char* GetName() const { return m_Name; }

	private:
		unsigned int m_UniqueId;
		
		char* m_Name;
		Transform m_Transform;
		Shared<Mesh> m_Mesh;
		Shared<Material> m_Material;

		static unsigned int s_UidFactory;
	};
}