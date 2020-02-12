#include "pch.h"
#include "Scene.h"

namespace Meander
{
	SceneNode* Scene::CreateNode()
	{
		SceneNode* node = new SceneNode();
		m_Nodes.push_back(node);
		return node;
	}

	SceneNode* Scene::CreateNode(const Transform& transform)
	{
		SceneNode* node = new SceneNode();
		node->GetTransform() = transform;
		m_Nodes.push_back(node);
		return node;
	}

	SceneNode* Scene::CreateNode(const Transform& transform, const Shared<Mesh> mesh, const Shared<Material> material)
	{
		SceneNode* node = new SceneNode();
		node->GetTransform() = transform;
		node->SetMesh(mesh);
		node->SetMaterial(material);
		m_Nodes.push_back(node);
		return node;
	}
}