#include "Graphite/Core/grpch.h"

#include "grLayer.h"

namespace Graphite
{
	grLayer::grLayer(): m_Name("") {}
	
	grLayer::grLayer(const std::string& name): m_Name(name) {}
	
	grLayer::~grLayer() {}
	
}
