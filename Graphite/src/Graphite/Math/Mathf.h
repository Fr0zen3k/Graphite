#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_MATHF_H
#define GRAPHITE_MATHF_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"


namespace Graphite
{
	namespace Math
	{
		// useful math functions
		// glm can be used for lerp and slerp
		class GRAPHITE_API Mathf
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
		};
	}
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif