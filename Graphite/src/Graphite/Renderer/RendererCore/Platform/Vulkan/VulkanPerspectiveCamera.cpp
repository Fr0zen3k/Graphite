#include "Graphite/Core/grpch.h"
#include "VulkanPerspectiveCamera.h"

#include "../../../Renderer3D/Renderer3D.h"
#include "VulkanGraphicsContext.h"
#include "../../GraphicsContext.h"

namespace Graphite {

	VulkanPerspectiveCamera::VulkanPerspectiveCamera()
	{
		// Initialize the projection matrix
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f * Application::Get()->GetWindow()->GetWidth() / Application::Get()->GetWindow()->GetHeight(), 0.001f, 100.0f);
		m_ProjectionMatrix[1][1] *= -1.0f;
		m_ViewFrustum = ViewFrustum(m_ProjectionMatrix);
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
		glm::mat4 m = glm::inverse(m_Transform.GetModelMatrix());
		m[0] = glm::normalize(m[0]);
		m[1] = glm::normalize(m[1]);
		m[2] = glm::normalize(m[2]);
		return m;
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
		m_Viewport.width = (float)Application::Get()->GetWindow()->GetWidth();
		m_Viewport.height = (float)Application::Get()->GetWindow()->GetHeight();
		m_Viewport.minDepth = 0.0f;
		m_Viewport.maxDepth = 1.0f;

		m_Scissors = {};
		m_Scissors.offset = { 0, 0 };
		m_Scissors.extent = GR_GRAPHICS_CONTEXT->GetSwapchainExtent();
	}

	bool VulkanPerspectiveCamera::InViewFrustum(BoundingSphere sphere, glm::vec3 position) const
	{
		glm::mat4 view = GetViewMatrix();
		glm::vec4 newPos = view * glm::vec4(position, 1.0f);

		return m_ViewFrustum.Check(sphere, glm::vec3(newPos.x / newPos.w, newPos.y / newPos.w, newPos.z / newPos.w));
	}

}