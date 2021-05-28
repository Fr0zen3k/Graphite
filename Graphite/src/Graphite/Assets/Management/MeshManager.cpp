#include "Graphite/Core/grpch.h"
#include "MeshManager.h"

namespace Graphite
{
	std::vector<std::vector<Mesh*>> MeshManager::s_MeshList;
	
	void MeshManager::Init()
	{
		std::vector<Mesh*> v(1, nullptr);
		s_MeshList.emplace_back(v);
	}

	void MeshManager::Shutdown()
	{
		for(auto v : s_MeshList)
		{
			for(Mesh* m : v)
			{
				delete m;
			}
		}
	}

	Mesh* MeshManager::GetMesh(MeshID mesh, float lodLevel)
	{
		int lodIndex = (int)(lodLevel * (s_MeshList[mesh].size() - 1));
		return s_MeshList[mesh][lodIndex];
	}

	MeshID MeshManager::AddMesh(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer)
	{
		if(vertexBuffer.size() == 0 || indexBuffer.size() == 0)
		{
			return 0;
		}

		Mesh* m = new Mesh(vertexBuffer, indexBuffer);
		std::vector<Mesh*> meshes;
		meshes.emplace_back(m);
		s_MeshList.emplace_back(meshes);

		return s_MeshList.size() - 1;
	}

	bool MeshManager::AddMeshLOD(MeshID mesh, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer)
	{
		if(mesh >= s_MeshList.size())
		{
			return false;
		}
		
		Mesh* m = new Mesh(vertexBuffer, indexBuffer);
		s_MeshList[mesh].emplace_back(m);

		return true;
	}
}
