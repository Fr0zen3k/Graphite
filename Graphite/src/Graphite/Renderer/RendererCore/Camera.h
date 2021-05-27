#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_CAMERA_H
#define GRAPHITE_CAMERA_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"
#include "Graphite/Math/Transform.h"

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Graphite/Math/BoundingSphere.h"

namespace Graphite
{

	enum class CameraType
	{
		None,
		Orthographic,
		Perspective
	};

#define GR_CAMERA_CLASS_TYPE(type) inline static CameraType GetStaticType() { return CameraType::type; } \
								inline virtual CameraType GetCameraType() const override { return GetStaticType(); }
	
	class GRAPHITE_API Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual bool OnEvent(const Event& e) = 0;

		virtual glm::vec3 GetPosition() const = 0;
		virtual glm::mat4 GetViewMatrix() const = 0;
		virtual glm::mat4 GetProjectionMatrix() const = 0;

		virtual void Translate(glm::vec3 position) = 0;

		virtual void Rotate(float angle, glm::vec3 rotationVector) = 0;
		virtual void Rotate(Math::Rotation rotation) = 0;
		virtual void Rotate(glm::quat quaternion) = 0;
		virtual void Rotate(const std::vector<Math::Rotation>& rotations) = 0;
		virtual void Rotate(const std::vector<glm::quat>& quaternions) = 0;

		virtual void SetFieldOfViewDeg(float degFOV = 60.0f) = 0;
		virtual void SetFieldOfViewRad(float radFOV = 1.0f / 3.0f * glm::pi<float>()) = 0;

		virtual bool InViewFrustum(BoundingSphere sphere, glm::vec3 position) const = 0;

		virtual CameraType GetCameraType() const = 0;

		virtual float GetNear() const = 0;
		virtual float GetFar() const = 0;

		static Camera* CreateCamera(CameraType type);
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif