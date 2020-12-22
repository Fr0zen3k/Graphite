#include "Graphite/Core/grpch.h"
#include "Transform.h"
namespace Graphite
{
	namespace Math
	{
		class Transform
		{
		private:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 size;

		public:
			Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::quat rotation = glm::quat(1, 0, 0, 0), float size = 1) {
				this->position = position;
				this->rotation = rotation;
				this->size = size;
			}

			// vector doesn't need to be normalized, angle is given in degrees
			void rotate(glm::vec3& vec, float angle) {
				glm::normalize(vec);
				glm::quat quaternion = glm::quat(angle / 180 * glm::pi(), vec);
				rotation = rotation * quaternion;
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
			void rotate(std::vector<Rotation>& rotations) {
				for (Rotation rot : quaternions) {
					q.vec = glm::vec3.normalize(rot.vec);
					glm::quat quaternion = glm::quat(rot.angle / 180 * glm::pi(), rot.vec);
					rotation = rotation * quaternion;
				}
			}
			// use with glm's quaternions
			void rotate(glm::quat& quaternion) {
				rotation = rotation * quaternion;
			}
			void rotate(std::vector<glm::quat>& quaternions) {
				for (glm::quat q : quaternions)
					rotation = rotation * q;
			}

			void translate(glm::vec3& translation) {
				position = position + translation;
			}
			void setPosition(glm::vec3 position) {
				this->position = position;
			}
			glm::vec3 getPosition() {
				return position;
			}
			void setSize(glm::vec3 size) {
				this->size = size;
			}
			glm::mat4 getMatrix() {
				glm::mat4 r = mat4_cast(rotation);
				r[0] = r[0] * size.x;
				r[1] = r[1] * size.y;
				r[2] = r[2] * size.z;
				r[3] = glm::vec4(position.x, position.y, position.z, 1);
				return r;
			}
		};

		// (vec3 doesn't have to be normalized, angle is given in degrees)
		struct Rotation {
			glm::vec3 vec;
			float angle;
		};
	}
}