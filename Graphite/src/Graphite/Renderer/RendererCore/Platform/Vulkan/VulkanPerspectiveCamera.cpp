#include "Graphite/Core/grpch.h"
#include "VulkanPerspectiveCamera.h"

#include "../../../Renderer2D/Renderer2D.h"
#include "VulkanGraphicsContext.h"
#include "../../GraphicsContext.h"

namespace Graphite {

	VulkanPerspectiveCamera::VulkanPerspectiveCamera()
	{
		// Initialize the projection matrix
		Init();
		m_Transform = Math::Transform();
	}

	bool VulkanPerspectiveCamera::OnEvent(const Event& e)
	{
		return false;
	}

	glm::vec3 VulkanPerspectiveCamera::GetPosition() const
	{
		return m_Transform.GetPosition();
	}

	glm::mat4 VulkanPerspectiveCamera::GetViewMatrix() const
	{
		return m_Transform.GetModelMatrix();
	}

	glm::mat4 VulkanPerspectiveCamera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	void VulkanPerspectiveCamera::Translate(glm::vec3 position)
	{
		m_Transform.Translate(position);
	}

	void VulkanPerspectiveCamera::Rotate(float angle, glm::vec3 rotationVector)
	{
		m_Transform.Rotate(rotationVector, angle);
	}

	void VulkanPerspectiveCamera::Rotate(Math::Rotation rotation)
	{
		m_Transform.Rotate(rotation.vec, rotation.angle);
	}

	void VulkanPerspectiveCamera::Rotate(glm::quat quaternion)
	{
		m_Transform.Rotate(quaternion);
	}

	void VulkanPerspectiveCamera::Rotate(const std::vector<Math::Rotation>& rotations)
	{
		m_Transform.Rotate(rotations);
	}

	void VulkanPerspectiveCamera::Rotate(const std::vector<glm::quat>& quaternions)
	{
		m_Transform.Rotate(quaternions);
	}

	void VulkanPerspectiveCamera::Init()
	{
		// Add viewport and scissor creations and extend functionality later

		m_Viewport = {};
		m_Viewport.x = 0.0f;
		m_Viewport.y = 0.0f;
		m_Viewport.width = (float)GR_GRAPHICS_CONTEXT->GetFrameSize().first;
		m_Viewport.height = (float)GR_GRAPHICS_CONTEXT->GetFrameSize().second;
		m_Viewport.minDepth = 0.0f;
		m_Viewport.maxDepth = 1.0f;

		m_Scissors = {};
		m_Scissors.offset = { 0, 0 };
		m_Scissors.extent = GR_GRAPHICS_CONTEXT->GetSwapchainExtent();
	}

}