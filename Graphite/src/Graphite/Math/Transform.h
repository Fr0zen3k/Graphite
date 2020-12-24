#pragma once
#include "Graphite/Core/grpch.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
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
			Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::quat rotation = glm::quat(1, 0, 0, 0), float size = 1);

			void rotate(glm::vec3& vec, float angle);
			void rotate(std::vector<Rotation>& rotations);
			void rotate(glm::quat& quaternion);
			void rotate(std::vector<glm::quat>& quaternions);

			void translate(glm::vec3& translation);

			void setPosition(glm::vec3 position);

			glm::vec3 getPosition();

			void setSize(glm::vec3 size);

			glm::mat4 getMatrix();
		}
		struct Rotation {
			glm::vec3 vec;
			float angle;
		};
	}
}