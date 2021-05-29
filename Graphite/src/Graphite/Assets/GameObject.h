#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_GAMEOBJECT_H
#define GRAPHITE_GAMEOBJECT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Graphite/Math/Transform.h"
#include "Graphite/Math/BoundingSphere.h"
#include "Material.h"
#include "MeshCore/Mesh.h"
#include "Graphite/Renderer/RendererCore/Texture.h"

namespace Graphite {

	class GRAPHITE_API GameObject
	{
	public:
		GameObject(const std::string& meshPath = "", const std::string& texturePath = "");
		virtual ~GameObject();
		
		inline Math::Transform& GetTransform() { return m_Transform; }
		BoundingSphere GetBoundingSphere() const;
		inline Material& GetMaterial() { return m_Material; }

		void AddLOD(const std::string& path);

		Mesh* GetMesh(float lodLevel = 1.0f) const;
		Texture* GetTexture() const;

		inline void SetMaterial(const Material& material) { m_Material = material; }
		
	private:
		void InitMesh(const std::string& path);
		void InitTexture(const std::string& path);

	private:
		Math::Transform m_Transform;
		std::vector<Mesh*> m_MeshLOD;
		Texture* m_Texture;
		Material m_Material;
	};

}

#endif


#if defined (_MSC_VER)
#pragma warning(pop)
#endif