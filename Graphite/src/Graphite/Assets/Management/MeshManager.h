#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_MESHMANAGER_H
#define GRAPHITE_MESHMANAGER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../MeshCore/Mesh.h"
#include "Graphite/Renderer/RendererCore/Utilities.h"


namespace Graphite
{

	class GRAPHITE_API MeshManager
	{
	public:
		static void Init();
		static void Shutdown();

		static Mesh* GetMesh(MeshID mesh, float lodLevel = 0.0f);

		static MeshID AddMesh(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer);
		static bool AddMeshLOD(MeshID mesh, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer);
		
	private:
		static std::vector<std::vector<Mesh*>> s_MeshList;
		
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif