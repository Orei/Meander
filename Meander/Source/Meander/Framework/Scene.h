#pragma once
#include "SceneNode.h"

namespace Meander
{
	class Mesh;
	class Material;

	class Scene
	{
	public:
		SceneNode* CreateNode();
		SceneNode* CreateNode(const Transform& transform);
		SceneNode* CreateNode(const Transform& transform, const Shared<Mesh> mesh, const Shared<Material> material);

		std::vector<SceneNode*> GetNodes() const { return m_Nodes; }

	private:
		std::vector<SceneNode*> m_Nodes;
	};
}