#pragma once
#include "Meander/Transform.h"

#define SCENE_NODE_NAME_LENGTH 32

namespace Meander
{
	class Mesh;
	class Material;

	class SceneNode
	{
	public:
		SceneNode(const char* name = nullptr) 
			: m_UniqueId(s_UidFactory++)
		{
			m_Name = new char[SCENE_NODE_NAME_LENGTH];
			SetName(name);
		}

		void SetName(const char* name);
		void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
		void SetMaterial(Material* material) { m_Material = material; }

		Transform& GetTransform() { return m_Transform; }
		Mesh* GetMesh() const { return m_Mesh; }
		Material* GetMaterial() const { return m_Material; }

		const char* GetName() const { return m_Name; }
		unsigned int GetUniqueId() const { return m_UniqueId; }

	private:
		unsigned int m_UniqueId = 0;
		char* m_Name = nullptr;
		Transform m_Transform = {};
		Mesh* m_Mesh = nullptr;
		Material* m_Material = nullptr;

		static unsigned int s_UidFactory;
	};
}