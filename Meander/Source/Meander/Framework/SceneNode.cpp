#include "pch.h"
#include "SceneNode.h"
#include "Meander/Common.h"

namespace Meander
{
	unsigned int SceneNode::s_UidFactory = 0;
	
	void SceneNode::SetName(const char* name)
	{
		// Default name if nullptr, this can't exceed 32 characters
		if (name == nullptr)
		{
			sprintf_s(m_Name, SCENE_NODE_NAME_LENGTH, "Node %i", s_UidFactory);
			return;
		}

		// Ensure we're not exceeding length
		if (strlen(name) > SCENE_NODE_NAME_LENGTH)
		{
			MN_WARN("Scene Node name exceeds the expected length.");
			return;
		}

		sprintf_s(m_Name, SCENE_NODE_NAME_LENGTH, name);
	}
}