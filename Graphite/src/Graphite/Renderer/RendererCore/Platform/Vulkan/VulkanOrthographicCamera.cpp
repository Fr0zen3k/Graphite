#include "Graphite/Core/grpch.h"
#include "VulkanOrthographicCamera.h"

#include "../../../Renderer2D/Renderer2D.h"
#include "VulkanGraphicsContext.h"
#include "../../GraphicsContext.h"

Graphite::VulkanOrthographicCamera::VulkanOrthographicCamera()
{
	Init();
	m_Transform = Math::Transform();
}

bool Graphite::VulkanOrthographicCamera::OnEvent(const Event& e)
{
	return false;
}

glm::vec3 Graphite::VulkanOrthographicCamera::GetPosition() const
{
	return m_Transform.GetPosition();
}

glm::mat4 Graphite::VulkanOrthographicCamera::GetViewMatrix() const
{
	return m_Transform.GetModelMatrix();
}

glm::mat4 Graphite::VulkanOrthographicCamera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

void Graphite::VulkanOrthographicCamera::Translate(glm::vec3 position)
{
	m_Transform.Translate(position);
}

void Graphite::VulkanOrthographicCamera::Rotate(float angle, glm::vec3 rotationVector)
{
	m_Transform.Rotate(rotationVector, angle);
}

void Graphite::VulkanOrthographicCamera::Rotate(Math::Rotation rotation)
{
	m_Transform.Rotate(rotation.vec, rotation.angle);
}

void Graphite::VulkanOrthographicCamera::Rotate(glm::quat quaternion)
{
	m_Transform.Rotate(quaternion);
}

void Graphite::VulkanOrthographicCamera::Rotate(const std::vector<Math::Rotation>& rotations)
{
	m_Transform.Rotate(rotations);
}

void Graphite::VulkanOrthographicCamera::Rotate(const std::vector<glm::quat>& quaternions)
{
	m_Transform.Rotate(quaternions);
}

void Graphite::VulkanOrthographicCamera::Init()
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
