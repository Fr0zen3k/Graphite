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

#include "glm/gtx/string_cast.hpp"


namespace Graphite
{
	GraphicsContext* Renderer3D::s_GraphicsContext = nullptr;
	RendererSettings Renderer3D::s_Settings;
	
	void Renderer3D::Init()
	{
		GameObjectManager::Init();
		
		try
		{
			s_GraphicsContext = GraphicsContext::GetContext();
		}
		catch (std::runtime_error& e)
		{
			GR_LOG_CRITICAL(e.what());
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
			GR_LOG_CRITICAL(e.what());
		}
	}

	void Renderer3D::OnTick()
	{
		uint32_t i = VulkanRendererAPI::StartDrawing();

		Camera* camera = Application::Get()->GetActiveCameraInstance();

		// TEST

		int drawCount = 1;
		uint32_t vertexCount = 0, indexCount = 0;
		double totalDrawLength = 0.0;
		std::chrono::high_resolution_clock::time_point start;
		
		// TEST

		
		// TEST
		start = std::chrono::high_resolution_clock::now();
		// TEST
		
		VulkanRendererAPI::Draw(i, nullptr, nullptr, nullptr, glm::mat4(1.0f), Material());

		// TEST
		totalDrawLength += std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count();
		// TEST
		
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

				// TEST
				start = std::chrono::high_resolution_clock::now();
				// TEST
				
				VulkanRendererAPI::Draw(i, vertexBuffer, indexBuffer, texture, model, material);

				// TEST
				totalDrawLength += std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count();
				// TEST

				// TEST

				drawCount++;
				vertexCount += vertexBuffer->Size();
				indexCount += indexBuffer->Size();

				// TEST
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

				// TEST
				start = std::chrono::high_resolution_clock::now();
				// TEST
				
				VulkanRendererAPI::Draw(i, vertexBuffer, indexBuffer, texture, model, material);

				// TEST
				totalDrawLength += std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count();
				// TEST

				// TEST

				drawCount++;
				vertexCount += vertexBuffer->Size();
				indexCount += indexBuffer->Size();

				// TEST
			}
		}
		
		VulkanRendererAPI::EndDrawing(&i);

		Application::Get()->GetBenchmarker()->SetDrawCallCount(drawCount);
		Application::Get()->GetBenchmarker()->SetVertexCount(vertexCount);
		Application::Get()->GetBenchmarker()->SetIndexCount(indexCount);
		Application::Get()->GetBenchmarker()->SetAvgDrawCall(totalDrawLength / drawCount);
	}

	void Renderer3D::Shutdown()
	{
		VulkanRendererAPI::Shutdown();
		delete s_GraphicsContext;

		GameObjectManager::Shutdown();
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
