#include "../Core/grpch.h"
#include "Transform.h"
namespace Graphite
{
	namespace Math
	{
		Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 size) : m_Position(position), m_Rotation(rotation) {
			m_Size = glm::vec3(1.0f, 1.0f, 1.0f) * size;
		}

		// vector doesn't need to be normalized, angle is given in degrees
		void Transform::Rotate(glm::vec3& vec, float angle) {
			glm::normalize(vec);
			glm::quat quaternion = glm::quat(angle / 180 * glm::pi<float>(), vec);
			m_Rotation = m_Rotation * quaternion;
		}
		// use with your quaternions, 
		// defined with struct Quaternion and packed into std::vector (you can give more than one quaternion)
		// example of use: 
		//  1) std::vector<Rotation> arg = new std::vector<Rotation>()
		//	2) Rotation rot;
		//  3) rot.vec = new glm::vec3(1, -1, -1);
		//  4) rot.angle = 180;
		//  5) arg.push_back(q);
		//  6) ... again 3 to 5 if you want to add more quaternions
		//	7) transform.rotate(arg); 
		void Transform::Rotate(std::vector<Rotation>& rotations) {
			for (Rotation rot : rotations) {
				rot.vec = glm::normalize(rot.vec);
				glm::quat quaternion = glm::quat(rot.angle / 180 * glm::pi<float>(), rot.vec);
				m_Rotation = m_Rotation * quaternion;
			}
		}
		// use with glm's quaternions
		void Transform::Rotate(glm::quat& quaternion) {
			m_Rotation = m_Rotation * quaternion;
		}
		void Transform::Rotate(std::vector<glm::quat>& quaternions) {
			for (glm::quat q : quaternions)
			{
				m_Rotation = m_Rotation * q;
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