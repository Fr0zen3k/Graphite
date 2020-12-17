#include "Graphite/Core/grpch.h"
#include "Transform.h"
namespace Math
{
	class Transform
	{
	private:
		glm::vec3 position;
		glm::quat rotation;
		float size;

	public:
		Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::quat rotation = glm::quat(1, 0, 0, 0), float size = 1) {
			this->position = position;
			this->rotation = rotation;
			this->size = size;
		}
		void rotate(std::vector<Quaternion>& quaternions){
			for (Quaternion q : quaternions) {
				glm::quat quaternion = glm::quat(q.angle, q.v);
				rotation = rotation * quaternion;
			}
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
		void setSize(float size) {
			this->size = size;
		}
		glm::mat4 getMatrix() {
			glm::mat4 r = mat4_cast(rotation);
			r = r * size;
			r[3] = glm::vec4(position.x, position.y, position.z, 1);
			return r;
		}
	};

	// v je normaliziran, angle je u radijanima
	struct Quaternion {
		glm::vec3 v;
		float angle;
	};
}