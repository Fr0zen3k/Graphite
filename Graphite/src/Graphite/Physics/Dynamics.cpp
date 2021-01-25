#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Application.h"
#include "Dynamics.h"

namespace Graphite
{
	namespace Physics
	{
		Dynamics::Dynamics(float mass = 1.0f, float elasticity = 0.0f,
			glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 acceleration = glm::vec3(0.0f, -9.81f, 0.0f),
			glm::vec3 torque = glm::vec3(0.0f, 0.0f, 0.0f)) :
				d_Mass(mass), d_Elasticity(elasticity), d_Force(force), d_Velocity(velocity), d_Acceleration(acceleration)
		{
			AddAcceleration(force / mass);
			d_Torque = glm::quat(torque.length() / mass, glm::normalize(torque));
		}

		void Dynamics::AddForce(glm::vec3& force) { d_Force += force; }

		void Dynamics::AddAcceleration(glm::vec3& acceleration) { d_Acceleration += acceleration; }

		void Dynamics::AddVelocity(glm::vec3& velocity) { d_Velocity += velocity; }

		void Dynamics::TimeTick(Transform& transform) // reference transform of the object
		{
			// translation
			AddAcceleration(force / mass);
			AddVelocity(d_Acceleration * Application::Tick());
			transform.Translate(d_Velocity * Application::Tick());

			// rotation
			glm::quat angularAcceleration = glm::cross(glm::quat(torque.length() / mass, glm::normalize(torque), angularAcceleration);
			d_AngularVelocity = glm::slerp(d_AngularVelocity, angularAcceleration, Application::Tick());
			transform.Rotate(glm::slerp(transform.GetQuat(), glm::cross(d_AngularVelocity, transform.GetQuat()), Application::Tick()));
		}
	}
}