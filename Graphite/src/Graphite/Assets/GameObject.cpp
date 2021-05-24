#include "Graphite/Core/grpch.h"
#include "GameObject.h"


#include "Management/MeshManager.h"
#include "Management/TextureManager.h"

namespace Graphite
{

	GameObject::GameObject(const std::string& meshPath, const std::string& texturePath)
	{
		InitMesh(meshPath);
		InitTexture(texturePath);
	}
	
	void GameObject::AddLOD(const std::string& path)
	{

	}

	Mesh* GameObject::GetMesh(float lodLevel) const
	{
		return MeshManager::GetMesh(m_Mesh, lodLevel);
	}

	Texture* GameObject::GetTexture() const
	{
		return TextureManager::GetTexture(m_Texture);
	}

	void GameObject::InitMesh(const std::string& path)
	{

	}

	void GameObject::InitTexture(const std::string& path)
	{
		m_Texture = TextureManager::AddTexture(path);
	}

	BoundingSphere GameObject::GetBoundingSphere() const
	{
		Mesh* m = GetMesh();
		glm::mat4 model = m_Transform.GetModelMatrix();
		float radius = m->GetMaxDistance() * std::max(glm::length(model[0]), std::max(glm::length(model[1]), glm::length(model[2])));
		return BoundingSphere(radius);
	}
	
}
