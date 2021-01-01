#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_TRANSFORM_H
#define GRAPHITE_TRANSFORM_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Graphite
{
	namespace Math
	{

		struct Rotation {
			glm::vec3 vec;
			float angle;
		};
		
		class GRAPHITE_API Transform
		{
		public:
			Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
			virtual ~Transform() = default;
			
			void Rotate(glm::vec3& vec, float angle);
			void Rotate(const std::vector<Rotation>& rotations);
			void Rotate(glm::quat& quaternion);
			void Rotate(const std::vector<glm::quat>& quaternions);

			inline void Translate(glm::vec3& translation) { m_Position = translation; }

			inline glm::vec3 GetPosition() const { return m_Position; }
			inline glm::vec3 GetSize() const { return m_Size; }

			inline void SetSize(glm::vec3 size) { m_Size = size; }

			glm::mat4 GetModelMatrix() const;

		private:
			glm::vec3 m_Position;
			glm::quat m_Rotation;
			glm::vec3 m_Size;

		};
		
	}
}

#endif
