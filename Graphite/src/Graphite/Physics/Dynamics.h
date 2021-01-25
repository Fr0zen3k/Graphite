#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include "Graphite/Math/Transform.h"

namespace Graphite
{
	namespace Physics
	{
		/// <summary>
		///  Game objects should use Dynamics to achieve physics behaviour (movement caused by aplying force to an object)
		///  If a game object doesn't have Dynamics, it will be treated as immovable object
		/// </summary>
		class GRAPHITE_API Dynamics
		{
		private:
			float d_Mass;
			glm::vec3 d_Force;
			glm::vec3 d_Velocity;
			glm::vec3 d_Acceleration;
			glm::vec3 d_Torque;
			glm::quat d_AngularVelocity; // can't handle more than one torque
			float d_Elasticity; // Used to calculate coefficient of restitution

		public:
			/// <summary>
			/// Define initial dynamics, all of the parameters are optional
			/// </summary>
			/// <param name="mass">-> affects inertness of the object, default value = 1</param>
			/// <param name="elasticity">-> affects how much energy is transformed to an object in collision (used to calculate coefficiente of restitution in a collision), default value = 0. Example1: object with elasticity = 1 will bounce off the immovable object with 100% preserved kinetic energy, while object with elasticity = 0 would loose all of it's kinetic energy. Example2: if two dynamic objects collide, coefficient of restitution is calculated by multiplying their elasticity.</param>
			/// <param name="force">-> initial force acting upon center of the object given as vector, default value = null vector (no force)</param>
			/// <param name="velocity">-> initial velocity of the object given as vector, default value = null vector (no velocity)</param>
			/// <param name="acceleration">-> initial acceleration of the object given as vector, default value = null vector (no acceleration, not even gravity)</param>
			/// <param name="torque">-> initial torque acting upon center of the object given as vector (used only for rotation of the object, not for rotation of force, velocity or acceleration of the object), default value = null vector (no torque)</param>
			Dynamics(float mass = 1.0f, float elasticity = 0.0f,
				glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 torque = glm::vec3(0.0f, 0.0f, 0.0f));

			/// <summary>
			/// Sets the mass of the object
			/// </summary>
			/// <param name="mass"></param>
			inline void SetMass(float mass) { d_Mass = mass; }

			/// <summary>
			/// Sets result force acting upon the object (combines all forces) by given vector force (length of the vector is magnitude of the force)
			/// </summary>
			/// <param name="force"></param>
			inline void SetForce(glm::vec3 force) { d_Force = force; }

			/// <summary>
			/// Adds a force acting upon the object by given vector (length of the vector is magnitude of the force).
			/// To add a force by given direction (vector) and magnitude of the force, firstly normalize direction vector, then simply multiply it by magnitude to get force vector
			/// </summary>
			/// <param name="force"></param>
			void AddForce(glm::vec3& force);

			/// <summary>
			/// Sets the velocity of an object by given vector (length of the vector is speed)
			/// </summary>
			/// <param name="velocity"></param>
			inline void SetVelocity(glm::vec3 velocity) { d_Velocity = velocity; }

			/// <summary>
			/// Adds a velocity of the object by given vector (length of the vector is magnitude of the force).
			/// To add a velocity by given direction (vector) and speed, firstly normalize direction vector, then simply multiply it by speed to get velocity vector
			/// </summary>
			/// <param name="velocity"></param>
			void AddVelocity(glm::vec3& velocity);
			
			/// <summary>
			/// Sets result acceleration of the object (combines all accelerations, including gravity). Length of the vector is magnitude of the acceleration)
			/// </summary>
			/// <param name="acceleration"></param>
			inline void SetAcceleration(glm::vec3 acceleration) { d_Acceleration = acceleration; }

			/// <summary>
			/// Adds an acceleration to an object by given vector (length of the vector is magnitude of the acceleration)
			/// To add an acceleration by given direction (vector) and magnitude of the acceleration, firstly normalize direction vector, then simply multiply it by magnitude to get acceleration vector
			/// </summary>
			/// <param name="acceleration"></param>
			void AddAcceleration(glm::vec3& acceleration);

			/// <summary>
			/// Sets torque to the object, center of the torque is center of the object, angular momentum = mass of the object * 1
			/// </summary>
			/// <param name="torque"></param>
			inline void SetTorque(glm::vec3& torque) { d_Torque = torque; }

			/// <summary>
			/// This function uses game loop to translate and rotate object (should be called for every frame)
			/// </summary>
			/// <param name="transform">-> reference to the Transform atribute of the object</param>
			void TimeTick(Transform& transform);
		};
	}
}

#if defined (_MSC_VER)
#pragma warning(pop)
#endif