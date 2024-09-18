#include "EditorSceneObject.h"

namespace bee {

	EditorSceneObject::EditorSceneObject(const char* name, const char* path) :
		m_name{ name }, m_path{path}
	{
		glm::vec3& pos = Get<be::Transform>().position;
		pos.x = 0; pos.y = 0; pos.z = 0;
		be::MeshRenderer& mr = Add<be::MeshRenderer>();
		be::ModelLoader::Load(path, mr);
		for (be::Mesh& mesh : mr.meshes)
		{
			mesh.SetupMesh();
		}
	}

	const char* EditorSceneObject::GetName() const
	{
		return m_name.c_str();
	}

	const char* EditorSceneObject::GetPath() const
	{
		return m_path.c_str();
	}

	void EditorSceneObject::SetName(const char* name)
	{
		m_name = name;
	}

}