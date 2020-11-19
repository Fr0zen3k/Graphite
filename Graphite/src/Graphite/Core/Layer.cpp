#include "Graphite/Core/grpch.h"

#include "Layer.h"

namespace Graphite
{
	Layer::Layer(): m_Name("") {}
	
	Layer::Layer(const std::string& name): m_Name(name) {}
	
	Layer::~Layer() {}
	
}
