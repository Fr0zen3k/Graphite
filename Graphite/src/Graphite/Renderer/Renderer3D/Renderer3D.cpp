#include "Graphite/Core/grpch.h"
#include "Renderer3D.h"

#include "Graphite/Renderer/RendererCore/Platform/Vulkan/VulkanRendererAPI.h"
#include "Graphite/Renderer/RendererCore/Platform/Vulkan/VulkanIndexBuffer.h"
#include "Graphite/Renderer/RendererCore/Platform/Vulkan/VulkanVertexBuffer.h"
#include "Graphite/Renderer/RendererCore/Platform/Vulkan/VulkanTexture.h"
#include "Graphite/Renderer/RendererCore/Camera.h"
#include "Graphite/Renderer/RendererCore/VertexBuffer.h"
#include "Graphite/Renderer/RendererCore/IndexBuffer.h"
#include "Graphite/Renderer/RendererCore/Texture.h"

#include "Graphite/Assets/Management/GameObjectManager.h"

#include "Graphite/Core/Application.h"

namespace Graphite
{
	GraphicsContext* Renderer3D::s_GraphicsContext = nullptr;
	RendererSettings Renderer3D::s_Settings;
	
	void Renderer3D::Init()
	{
		try
		{
			s_GraphicsContext = GraphicsContext::GetContext();
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void Renderer3D::InitAPI()
	{
		try
		{
			VulkanRendererAPI::Init();
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void Renderer3D::OnTick()
	{
		int i = VulkanRendererAPI::StartDrawing();

		Camera* camera = Application::Get()->GetActiveCameraInstance();

		for(GameObjectID id = 1; id < GameObjectManager::Size(); id++)
		{
			GameObject* object = GameObjectManager::GetGameObject(id);

			if(s_Settings.culling)
			{
				if(!camera->InViewFrustum(object->GetBoundingSphere(), object->GetTransform().GetPosition()))
				{
					continue;
				}

				Mesh* mesh;
				
				if(s_Settings.LOD)
				{
					float distance = glm::length(object->GetTransform().GetPosition() - camera->GetPosition()) - camera->GetNear();

					float lod = distance / (camera->GetFar() - camera->GetNear());
					
					mesh = object->GetMesh(lod);
				}
				else
				{
					mesh = object->GetMesh();
				}

				VulkanVertexBuffer* vertexBuffer = dynamic_cast<VulkanVertexBuffer*>(mesh->GetVertexBuffer());
				VulkanIndexBuffer* indexBuffer = dynamic_cast<VulkanIndexBuffer*>(mesh->GetIndexBuffer());
				VulkanTexture* texture = dynamic_cast<VulkanTexture*>(object->GetTexture());
				glm::mat4 model = object->GetTransform().GetModelMatrix();
				Material material = object->GetMaterial();

				VulkanRendererAPI::Draw(i, vertexBuffer, indexBuffer, texture, model, material);
			}
			else
			{
				Mesh* mesh;

				if (s_Settings.LOD)
				{
					float distance = glm::length(object->GetTransform().GetPosition() - camera->GetPosition()) - camera->GetNear();

					float lod = distance / (camera->GetFar() - camera->GetNear());

					mesh = object->GetMesh(lod);
				}
				else
				{
					mesh = object->GetMesh();
				}

				VulkanVertexBuffer* vertexBuffer = dynamic_cast<VulkanVertexBuffer*>(mesh->GetVertexBuffer());
				VulkanIndexBuffer* indexBuffer = dynamic_cast<VulkanIndexBuffer*>(mesh->GetIndexBuffer());
				VulkanTexture* texture = dynamic_cast<VulkanTexture*>(object->GetTexture());
				glm::mat4 model = object->GetTransform().GetModelMatrix();
				Material material = object->GetMaterial();

				VulkanRendererAPI::Draw(i, vertexBuffer, indexBuffer, texture, model, material);
			}
		}
		
		VulkanRendererAPI::EndDrawing(i);
	}

	void Renderer3D::Shutdown()
	{
		VulkanRendererAPI::Shutdown();
		delete s_GraphicsContext;
	}

	void Renderer3D::UpdateSettings(RendererSettings settings)
	{
		s_Settings = settings;
	}

	GraphicsContext* Renderer3D::GetGraphicsContext()
	{
		return s_GraphicsContext;
	}
}
