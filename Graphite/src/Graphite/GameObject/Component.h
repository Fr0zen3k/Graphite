#pragma once

#include "Entity.h"

#include <typeinfo>
#include <memory>
#include <vector>
#include <map>

namespace Graphite
{

	class Component
	{
	public:
		Component(Entity* e);
		virtual ~Component() = 0;

		Entity* entity() const { return mEntity; }

		// Returns a component of the owner entity. If the component doesn't exist throws std::out_of_range
		template <class _CompT>
		_CompT& part() const { return mEntity->part<_CompT>(); }

		// Returns a component pointer of the owner entity. If the component doesn't exist returns nullptr.
		template <class _CompT>
		_CompT* partPtr() const { return mEntity->partPtr<_CompT>(); }

	private:
		Entity* mEntity;
	};
}