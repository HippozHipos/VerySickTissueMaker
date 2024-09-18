#include "EditorSceneObject.h"

namespace bee {

	EditorSceneObject::EditorSceneObject(const char* path)
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

}