#pragma once

#include <typeinfo>

namespace Graphite
{
	class Component;

	class ComponentContainer
	{
	public:
		ComponentContainer() = 0;

		template <class _CompT>
		ComponentContainer(_CompT* c) :
			mComponentPtr(c),
			mTypeInfoPtr(&typeid(_CompT))
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "Component container can only contain Component objects");
		};

		inline Component* componentPtr() const { return mComponentPtr; }
		inline const std::type_info* typeInfoPtr() const { return mTypeInfoPtr; }

	private:
		Component* mComponentPtr;
		const std::type_info* mTypeInfoPtr;
	};
}