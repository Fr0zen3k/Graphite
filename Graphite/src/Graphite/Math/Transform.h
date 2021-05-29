#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
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
		struct GRAPHITE_API Rotation {
			glm::vec3 vec;
			float angle;
		};

		class GRAPHITE_API Transform
		{
		public:
			/// <summary>
			/// Construct transform, used for calculation of the transform matrix
			/// </summary>
			/// <param name="position"></param>
			/// <param name="rotation"></param>
			/// <param name="size">-> vector for resizing x, y, z of the initial object</param>
			Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
			virtual ~Transform() = default;

			/// <summary>
			/// Rotate object around axis defined by given vector for given angle
			/// </summary>
			/// <param name="vector"></param>
			/// <param name="angle"></param>
			void Rotate(glm::vec3& vector, float angle);

			/// <summary>
			/// Apply multiple rotations defined with structs Quaternion and packed into std::vector
			/// </summary>
			/// <param name="rotations"></param>
			void Rotate(const std::vector<Rotation>& rotations);
			// example of use :
			//  1) std::vector<Rotation> arg = new std::vector<Rotation>()
			//	2) Rotation rot;
			//  3) rot.vec = new glm::vec3(1, -1, -1);
			//  4) rot.angle = 180;
			//  5) arg.push_back(q);
			//  6) ... again 3 to 5 if you want to add more quaternions
			//	7) transform.rotate(arg); 

			/// <summary>
			/// Rotate by given quaternion
			/// </summary>
			/// <param name="quaternion"></param>
			void Rotate(glm::quat& quaternion);

			/// <summary>
			/// Apply multiple rotations defined with quaternions
			/// </summary>
			/// <param name="quaternions"></param>
			void Rotate(const std::vector<glm::quat>& quaternions);

			/// <summary>
			/// Change the position by translating for the given vector
			/// </summary>
			/// <param name="translation"></param>
			inline void Translate(const glm::vec3& translation) { m_Position = translation; }

			/// <returns>position</returns>
			inline glm::vec3 GetPosition() const { return m_Position; }

			/// <returns>size coeficients</returns>
			inline glm::vec3 GetSize() const { return m_Size; }

			/// <returns>quaternion used for rotations</returns>
			inline glm::quat GetQuat() const { return m_Rotation; }

			/// <summary>
			/// sets size coeficients
			/// </summary>
			/// <param name="size">vector that resizes x, y, z of the initial object</param>
			inline void SetSize(glm::vec3 size) { m_Size = size; }

			/// <returns>transformation matrix</returns>
			glm::mat4 GetModelMatrix() const;

		private:
			glm::vec3 m_Position;
			glm::quat m_Rotation;
			glm::vec3 m_Size;
		};
	}
}
#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif