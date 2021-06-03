#include "Graphite/Core/grpch.h"
#include "Transform.h"


namespace Graphite
{
	namespace Math
	{
		Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 size) : m_Position(position), m_Rotation(rotation) {
			m_Size = size;
		}

		void Transform::Rotate(glm::vec3& vector, float angle) {
			glm::quat quaternion = glm::quat(glm::cos(angle/2), glm::normalize(vector) * glm::sin(angle / 2));
			m_Rotation = quaternion * m_Rotation;
		}

		void Transform::Rotate(const std::vector<Rotation>& rotations) {
			for (Rotation rot : rotations) {
				glm::quat quaternion = glm::quat(glm::cos(rot.angle / 2), glm::normalize(rot.vec) * glm::sin(rot.angle / 2));
				m_Rotation *= quaternion;
				glm::normalize(m_Rotation);
			}
		}

		void Transform::Rotate(glm::quat& quaternion) {
			m_Rotation *= quaternion;
			glm::normalize(m_Rotation);
		}
		
		void Transform::Rotate(const std::vector<glm::quat>& quaternions) {
			for (glm::quat q : quaternions)
			{
				m_Rotation *= q;
			}

			glm::normalize(m_Rotation);
		}

		glm::mat4 Transform::GetModelMatrix() const {
			glm::mat4 r = glm::mat4_cast(m_Rotation);
			r[0] *= m_Size.x;
			r[1] *= m_Size.y;
			r[2] *= m_Size.z;
			r[3] = glm::vec4(m_Position.x, m_Position.y, m_Position.z, 1);
			return r;
		}
	}
}