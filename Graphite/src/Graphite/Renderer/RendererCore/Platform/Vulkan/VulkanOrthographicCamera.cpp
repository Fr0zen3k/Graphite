#include "Graphite/Core/grpch.h"
#include "VulkanOrthographicCamera.h"

#include "../../../Renderer3D/Renderer3D.h"
#include "VulkanGraphicsContext.h"
#include "../../GraphicsContext.h"

namespace Graphite {

	VulkanOrthographicCamera::VulkanOrthographicCamera()
	{
		Init();
		m_Transform = Math::Transform();
	}

	bool VulkanOrthographicCamera::OnEvent(const Event& e)
	{
		return false;
	}

	glm::vec3 VulkanOrthographicCamera::GetPosition() const
	{
		return m_Transform.GetPosition();
	}

	glm::mat4 VulkanOrthographicCamera::GetViewMatrix() const
	{
		glm::mat4 ret = m_Transform.GetModelMatrix();
		ret[0] *= 1.0f;
		ret[1] *= 1.0f;
		ret[2] *= 1.0f;
		ret = glm::inverse(ret);
		return ret;
	}

	glm::mat4 VulkanOrthographicCamera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	void VulkanOrthographicCamera::Translate(glm::vec3 position)
	{
		m_Transform.Translate(position);
	}

	void VulkanOrthographicCamera::Rotate(float angle, glm::vec3 rotationVector)
	{
		m_Transform.Rotate(rotationVector, angle);
	}

	void VulkanOrthographicCamera::Rotate(Math::Rotation rotation)
	{
		m_Transform.Rotate(rotation.vec, rotation.angle);
	}

	void VulkanOrthographicCamera::Rotate(glm::quat quaternion)
	{
		m_Transform.Rotate(quaternion);
	}

	void VulkanOrthographicCamera::Rotate(const std::vector<Math::Rotation>& rotations)
	{
		m_Transform.Rotate(rotations);
	}

	void VulkanOrthographicCamera::Rotate(const std::vector<glm::quat>& quaternions)
	{
		m_Transform.Rotate(quaternions);
	}

	void VulkanOrthographicCamera::Init()
	{
		m_ProjectionMatrix = glm::ortho(
			0.0f,
			(float)GR_GRAPHICS_CONTEXT->GetFrameSize().first,
			0.0f,
			(float)GR_GRAPHICS_CONTEXT->GetFrameSize().second);
	}

}