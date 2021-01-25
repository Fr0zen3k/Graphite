#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_COMPONENTCONTAINER_H
#define GRAPHITE_COMPONENTCONTAINER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Component.h"

namespace Graphite
{
	class GRAPHITE_API ComponentContainer
	{
	public:
		ComponentContainer() = delete;

		ComponentContainer(Component* c) :
			mComponentPtr(c),
			mTypeInfoPtr(&typeid(*c))
		{
			//static_assert(std::is_base_of<Component, _CompT>::value, "Component container can only contain Component objects");
		};

		inline Component* componentPtr() const { return mComponentPtr; }
		inline const std::type_info* typeInfoPtr() const { return mTypeInfoPtr; }

	private:
		Component* mComponentPtr;
		const std::type_info* mTypeInfoPtr;
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif