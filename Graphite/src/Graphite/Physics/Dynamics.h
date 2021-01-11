#pragma once

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include "Graphite/Math/Transform.h"

namespace Graphite
{
	namespace Physics
	{
		class GRAPHITE_API Dynamics
		{
		private:
			float d_Mass;
			glm::vec3 d_Force;
			glm::vec3 d_Velocity;
			glm::vec3 d_Acceleration;
			glm::vec3 d_Torque; // TODO: angular interpolation for quaternions
			float d_Elasticity; // TODO: elastiènost sudara

		public:
			Dynamics(float mass = 1.0f, float elasticity = 0.0f,
				glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 acceleration = glm::vec3(0.0f, -9.81f, 0.0f),
				glm::vec3 torque = glm::vec3(0.0f, 0.0f, 0.0f));

			// Sets the mass of the object
			inline void SetMass(float mass) { d_Mass = mass; }

			// Sets result force acting upon the object (combines all forces) by given vector force (length of the vector is magnitude of the force)
			inline void SetForce(glm::vec3 force) { d_Force = force; }

			// Adds a force acting upon the object by given vector (length of the vector is magnitude of the force)
			// To add a force by given direction (vector) and magnitude of the force, firstly normalize direction vector, then simply multiply it by magnitude to get force vector
			void AddForce(glm::vec3& force);

			// Sets the velocity of an object by given vector (length of the vector is speed)
			inline void SetVelocity(glm::vec3 velocity) { d_Velocity = velocity; }

			// Adds a velocity of the object by given vector (length of the vector is magnitude of the force)
			// To add a velocity by given direction (vector) and speed, firstly normalize direction vector, then simply multiply it by speed to get velocity vector
			void AddVelocity(glm::vec3& force);

			// Sets result acceleration of the object (combines all accelerations, including gravity) by given vector acceleration (length of the vector is magnitude of the acceleration)
			inline void SetAcceleration(glm::vec3 acceleration) { d_Acceleration = acceleration; }

			// Adds an acceleration to an object by given vector (length of the vector is magnitude of the acceleration)
			// To add an acceleration by given direction (vector) and magnitude of the acceleration, firstly normalize direction vector, then simply multiply it by magnitude to get acceleration vector
			void AddAcceleration(glm::vec3& acceleration);

			// This should be called every dt seconds
			void TimeTick(float dt);

			glm::mat4 GetTransformationMatrix() const;

		};
	}
}
