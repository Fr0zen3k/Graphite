#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANORTHOGRAPHICCAMERA_H
#define GRAPHITE_VULKANORTHOGRAPHICCAMERA_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/Math/Transform.h"
#include "Graphite/EventCore/Events.h"
#include "../../Camera.h"

#include "glm/glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include "vulkan/vulkan.h"

namespace Graphite
{
	
	class GRAPHITE_API VulkanOrthographicCamera: public Camera
	{
	public:
		VulkanOrthographicCamera();
		~VulkanOrthographicCamera() override = default;

		bool OnEvent(const Event& e) override;

		glm::vec3 GetPosition() const override;
		glm::mat4 GetViewMatrix() const override;
		glm::mat4 GetProjectionMatrix() const override;
		
		void Translate(glm::vec3 position) override;
		
		void Rotate(
			float angle,
			glm::vec3 rotationVector) override;
		void Rotate(Math::Rotation rotation) override;
		void Rotate(glm::quat quaternion) override;
		void Rotate(const std::vector<Math::Rotation>& rotations) override;
		void Rotate(const std::vector<glm::quat>& quaternions) override;

		GR_CAMERA_CLASS_TYPE(Orthographic)

		inline void SetFieldOfViewDeg(float degFOV = 60.0f) override { m_FieldOfView = glm::radians(degFOV); }
		inline void SetFieldOfViewRad(float radFOV = 1.0f / 3.0f * glm::pi<float>()) override { m_FieldOfView = radFOV; }

		inline bool InViewFrustum(BoundingSphere sphere, glm::vec3 position) const override { return true; };

		inline float GetNear() const override { return m_Near; }
		inline float GetFar() const override { return m_Far; }
		
	private:
		void Init();

	private:
		Math::Transform m_Transform;
		glm::mat4 m_ProjectionMatrix;
		float m_FieldOfView;
		float m_AspectRation;
		float m_Near = 0.001f;
		float m_Far = 1000.0f;
	};
	
}

#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif