	#include "Graphite/Core/grpch.h"
#include "GameObject.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


#include "glm/gtx/string_cast.hpp"

namespace Graphite
{

	GameObject::GameObject(const std::string& meshPath, const std::string& texturePath)
	{
		InitMesh(meshPath);
		InitTexture(texturePath);
	}

	GameObject::~GameObject()
	{
		delete m_Texture;

		for(Mesh* m : m_MeshLOD)
		{
			delete m;
		}
	}
	
	void GameObject::AddLOD(const std::string& path)
	{
		std::vector<Vertex> vertexBuffer;
		std::vector<uint32_t> indexBuffer;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!scene)
		{
			throw std::runtime_error(importer.GetErrorString());
		}

		if (scene->HasMeshes())
		{
			aiMesh* mesh = scene->mMeshes[0];

			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				glm::vec2 uv(mesh->mTextureCoords[i]->x, mesh->mTextureCoords[i]->y);

				Vertex v;
				v.position = position;
				v.normal = normal;
				v.textureCoords = uv;

				vertexBuffer.emplace_back(v);
			}

			for (int i = 0; i < mesh->mNumFaces; i++)
			{
				for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
				{
					indexBuffer.emplace_back(mesh->mFaces[i].mIndices[j]);
				}
			}

			glm::vec3 center(0.0f);

			for (int i = 0; i < vertexBuffer.size(); i++)
			{
				center += vertexBuffer[i].position;
			}

			center /= 1.0f * vertexBuffer.size();

			for (int i = 0; i < vertexBuffer.size(); i++)
			{
				vertexBuffer[i].position -= center;
			}

			Mesh* m = new Mesh(vertexBuffer, indexBuffer);
			m_MeshLOD.emplace_back(m);
		}
	}

	Mesh* GameObject::GetMesh(float lodLevel) const
	{
		if(lodLevel > 1.0f)
		{
			lodLevel = 1.0f;
		}

		if(lodLevel < 0.0f)
		{
			lodLevel = 0.0f;
		}
		
		int index = (1.0f - lodLevel) * (m_MeshLOD.size() - 1);
		return m_MeshLOD[index];
	}

	Texture* GameObject::GetTexture() const
	{
		return m_Texture;
	}

	void GameObject::InitMesh(const std::string& path)
	{
		std::vector<Vertex> vertexBuffer;
		std::vector<uint32_t> indexBuffer;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if(!scene)
		{
			throw std::runtime_error(importer.GetErrorString());
		}

		if(scene->HasMeshes())
		{
			aiMesh* mesh = scene->mMeshes[0];

			uint32_t materialIndex = mesh->mMaterialIndex;

			m_Material = Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 10.0f, 10.0f), 1.0f, 0.64f, 0.5f, 6.0f);

			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				glm::vec2 uv(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

				Vertex v;
				v.position = position;
				v.normal = normal;
				v.textureCoords = uv;

				vertexBuffer.emplace_back(v);
			}

			for(int i = 0; i < mesh->mNumFaces; i++)
			{
				for(int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
				{
					indexBuffer.emplace_back(mesh->mFaces[i].mIndices[j]);
				}
			}

			glm::vec3 center(0.0f);

			for(int i = 0; i < vertexBuffer.size(); i++)
			{
				center += vertexBuffer[i].position;
			}

			center /= 1.0f * vertexBuffer.size();

			for(int i = 0; i < vertexBuffer.size(); i++)
			{
				vertexBuffer[i].position -= center;
			}

			m_MeshLOD.emplace_back(new Mesh(vertexBuffer, indexBuffer));
		}
	}

	void GameObject::InitTexture(const std::string& path)
	{
		m_Texture = Texture::CreateTexture(path);
	}

	BoundingSphere GameObject::GetBoundingSphere() const
	{
		Mesh* m = GetMesh();
		glm::mat4 model = m_Transform.GetModelMatrix();
		float radius = m->GetMaxDistance() * std::max(glm::length(model[0]), std::max(glm::length(model[1]), glm::length(model[2])));
		return BoundingSphere(radius);
	}
	
}
