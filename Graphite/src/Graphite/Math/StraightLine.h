#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_STRAIGHTLINE_H
#define GRAPHITE_STRAIGHTLINE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

namespace Graphite {
	
	class GRAPHITE_API StraightLine
	{
	public:
		StraightLine() = default;
		StraightLine(const glm::vec3& point1, const glm::vec3& point2);
		virtual ~StraightLine() = default;

		bool PointOnLine(const glm::vec3& point) const;
		
		bool Parallel(const StraightLine& line) const;
		bool Parallel(const glm::vec3& vector) const;
		
		float Distance(const glm::vec3& point) const;

		glm::vec3 Get(float t) const;
	private:
		glm::mat4x2 m_Parameters;
	};
	
}

#endif


#if defined (_MSC_VER)
#pragma warning(pop)
#endif