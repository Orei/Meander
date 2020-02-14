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

	SceneNode* Scene::CreateNode(const Transform& transform, Mesh* mesh, Material* material)
	{
		SceneNode* node = new SceneNode();

		// Copy transform data
		node->GetTransform().SetPosition(transform.GetPosition());
		node->GetTransform().SetRotation(transform.GetRotation());
		node->GetTransform().SetScale(transform.GetScale());
		node->SetMesh(mesh);
		node->SetMaterial(material);

		m_Nodes.push_back(node);
		return node;
	}
}