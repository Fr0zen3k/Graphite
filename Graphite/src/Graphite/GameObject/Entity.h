#pragma once

#include "ComponentContainer.h"

#include <typeinfo>
#include <memory>
#include <vector>
#include <map>

namespace Graphite
{
	class Component;

	class Entity
	{
	public:
		Entity(std::vector<ComponentContainer> components);
		virtual ~Entity() = 0;

		// Returns a component. If the component doesn't exist throws std::out_of_range
		template <class _CompT>
		_CompT& part() const
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "The template arg is not a Component");
			
			return *static_cast<_CompT*>(
				mComponents.at(
					&typeid(_CompT)
				).get()
			);
		}

		// Returns a component pointer. If the component doesn't exist returns nullptr.
		template <class _CompT>
		_CompT* partPtr()
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "The template arg is not a Component");

			std::map<std::type_info*, std::unique_ptr<Component>>::iterator it = mComponents.find(&typeid(_CompT));

			if (it == mComponents.end())
				return nullptr;
			else
				return it->second.get();
		}

	private:
		std::map<std::type_info*, std::unique_ptr<Component>> mComponents;
	};
}