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
		SceneNode* CreateNode(const Transform& transform, Mesh* mesh = nullptr, Material* material = nullptr);

		std::vector<SceneNode*> GetNodes() const { return m_Nodes; }

	private:
		std::vector<SceneNode*> m_Nodes;
	};
}