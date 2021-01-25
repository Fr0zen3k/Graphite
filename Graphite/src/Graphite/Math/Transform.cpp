#include "../Core/grpch.h"
#include "Transform.h"
namespace Graphite
{
	namespace Math
	{
		Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 size) : m_Position(position), m_Rotation(rotation) {
			m_Size = glm::vec3(1.0f, 1.0f, 1.0f) * size;
		}

		void Transform::Rotate(glm::vec3& vector, float angle) {
			glm::normalize(vec);
			glm::quat quaternion = glm::quat(glm::radians(angle), vec);
			m_Rotation = quaternion * m_Rotation;
		}

		void Transform::Rotate(std::vector<Rotation>& rotations) {
			for (Rotation rot : rotations) {
				rot.vec = glm::normalize(rot.vec);
				glm::quat quaternion = glm::quat(glm::radians(angle), rot.vec);
				m_Rotation = glm::cross(quaternion, m_Rotation);
			}
		}

		void Transform::Rotate(glm::quat& quaternion) {
			m_Rotation = glm::cross(quaternion, m_Rotation);
		}
		void Transform::Rotate(std::vector<glm::quat>& quaternions) {
			for (glm::quat q : quaternions)
			{
				m_Rotation = glm::cross(q, m_Rotation);
			}
		}

		glm::mat4 Transform::GetModelMatrix() const {
			glm::mat4 r = glm::mat4_cast(m_Rotation);
			r[0] *= m_Size.x;
			r[1] *= m_Size.y;
			r[2] *= m_Size.z;
			r[3] *= glm::vec4(m_Position.x, m_Position.y, m_Position.z, 1);
			return r;
		}
	}
}