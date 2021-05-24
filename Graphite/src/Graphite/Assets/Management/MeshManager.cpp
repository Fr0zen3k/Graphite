#include "Graphite/Core/grpch.h"
#include "MeshManager.h"

namespace Graphite
{
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
	}

	bool MeshManager::AddMeshLOD(MeshID mesh, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer)
	{
		Mesh* m = new Mesh(vertexBuffer, indexBuffer);
		s_MeshList[mesh].emplace_back(m);
	}
}
