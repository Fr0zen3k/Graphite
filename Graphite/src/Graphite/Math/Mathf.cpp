#include "Graphite/Core/grpch.h"
#include "Mathf.h"

namespace Graphite
{
	namespace Math
	{
		void static Mathf::Lerp(float& start, float& stop, float& currentValue, float& rate) 
		{
			if (start < stop) {
				float tmp = currentValue + rate * (stop - start);
				if (tmp < stop + FLT_EPSILON)
					currentValue = tmp;
				else
					currentValue = stop;
			}
			else if (start > stop) {
				float tmp = currentValue + rate * (start - stop);
				if (tmp > stop + FLT_EPSILON)
					currentValue = tmp;
				else
					currentValue = stop;
			}
		}
	}
}
