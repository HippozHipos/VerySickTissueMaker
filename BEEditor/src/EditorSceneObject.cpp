#include "EditorSceneObject.h"

namespace bee {

	EditorSceneObject::EditorSceneObject(const char* name) :
		m_name{ name }
	{
	}

	const char* EditorSceneObject::GetName() const
	{
		return m_name.c_str();
	}

	void EditorSceneObject::SetName(const char* name)
	{
		m_name = name;
	}

}