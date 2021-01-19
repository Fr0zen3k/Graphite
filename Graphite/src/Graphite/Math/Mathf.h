#pragma once

#include "Graphite/Core/grpch.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace Graphite
{
	namespace Math
	{
		// useful math functions
		// glm can be used for lerp and slerp
		class Mathf
		{
		public:
			/// <summary>
			/// Linear interpolation. Every time this function is called another step (rate * length from start to stop) is added to currentValue until it's value becomes equal to stop
			/// </summary>
			/// <param name="start"></param>
			/// <param name="stop"></param>
			/// <param name="currentValue">- reference to the variable you whish to interpolate</param>
			/// <param name="rate">- step size, value between 0.0f and 1.0f</param>
			void static Lerp(float& start, float& stop, float& currentValue, float& rate);
		}
	}
}