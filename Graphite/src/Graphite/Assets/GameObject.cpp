#include "Graphite/Core/grpch.h"
#include "GameObject.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Management/MeshManager.h"
#include "Management/TextureManager.h"

namespace Graphite
{

	GameObject::GameObject(const std::string& meshPath)
	{
		InitMesh(meshPath);
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

			MeshManager::AddMeshLOD(m_Mesh, vertexBuffer, indexBuffer);
		}
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
			aiMaterial* material = scene->mMaterials[materialIndex];

			aiColor3D specular, ambient;
			material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);

			float shininess;
			material->Get(AI_MATKEY_SHININESS, shininess);

			m_Material = Material(glm::vec3(ambient.r, ambient.g, ambient.b), glm::vec3(specular.r, specular.g, specular.b), glm::vec3(0.0f, 0.0f, 3.0f), 1.0f, 1.0f, 1.0f, shininess);

			aiString texturePath;
			material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texturePath);

			InitTexture(texturePath.C_Str());

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

			m_Mesh = MeshManager::AddMesh(vertexBuffer, indexBuffer);
		}
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
