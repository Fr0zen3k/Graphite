#pragma once

#include "Graphite/Core/grpch.h"
#include <glm/glm.hpp>
#include "Transform.h"
#include "GeoEntity.h"

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API Box : GeoEntity
		{
		public:
			/// <summary>
			/// Constructs a box by defining dimensions and position of the box, transformation parameter is optional.
			/// By default orientation, edges of the box are colinear with base vectors: width (1,0,0), height (0,1,0), depth (0,0,1)
			/// </summary>
			/// <param name="size">-> Dimensions of the box are given as positive numbers using a vector size (width, height, depth)</param>
			/// <param name="position">-> Represents the location of the center of the box</param>
			/// <param name="transformation">-> Transformation can be used to change orientation or dimensions of the box (getters and setters of the class Transform)</param>
			Box(glm::vec3 size, glm::vec3 position, Transform transformation = Transform());
			virtual ~Box() = default;

			/// <returns>a point of the center of the box</returns>
			inline glm::vec3 GetPosition() const { return b_Transformation.GetPosition(); }

			/// <returns>size of the box as a vector (width, height, depth)</returns>
			inline glm::vec3 GetSize() const {
				glm::vec3 r = glm::vec3(b_Vertex * 2);
				glm::vec3 m_Size = b_Transformation.GetSize();
				r[0] *= m_Size.x;
				r[1] *= m_Size.y;
				r[2] *= m_Size.z;
				return r;
			}

			/// <summary>
			/// Transformation can be used to change position, orientation of the box or to resize the box (getters and setters of the class Transform)
			/// </summary>
			/// <returns>transformation atribute of the box</returns>
			inline Transform GetTransformation() const { return b_Transformation; }

			/// <summary>Transformation is used to change position or orientation of the box or to resize the box (getters and setters of the class Transform)</summary>
			inline void SetTransformation(Transform transformation) { b_Transformation = transformation; }

			/// <summary>
			/// Sets the position of the center of the box by given point
			/// </summary>
			/// <param name="point"></param>
			inline void SetPosition(glm::vec3 point) { b_Transformation.SetPosition(point); }

			/// <summary>
			/// Sets dimensions of the box by given vector size (width, height, depth)
			/// </summary>
			/// <param name="size"></param>
			inline void SetSize(glm::vec3 size) {
				b_Transformation.SetSize(glm::vec3(1.0f, 1.0f, 1.0f));
				b_Vertex = size * 0.5;
			}

		private:
			glm::vec3 b_Vertex;  // can produce all 8 vertexes, only by changing +/- of the vector components
			Transform b_Transformation;  // actual box is calculated in the moment of need
		};
	}
}