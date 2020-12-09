#pragma once
#include "Graphite/Core/grpch.h"
#include <glm/glm.hpp>

class GeoEntity
{
	// ne postoji virtual template metoda?
	template <class T>
	bool contains(T e);
};

