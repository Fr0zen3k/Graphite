//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "Entity.h"

#include <typeinfo>
#include <memory>
#include <vector>
#include <map>

namespace Graphite
{

	class GRAPHITE_API Component
	{
	public:
		Component();
		virtual ~Component() = 0;

		// Returns a component of the owner entity. If the component doesn't exist throws std::out_of_range
		template <class _CompT>
		_CompT& Comp() const { return mEntity->Comp<_CompT>(); }

		// Returns a component pointer of the owner entity. If the component doesn't exist returns nullptr.
		template <class _CompT>
		_CompT* CompPtr() const { return mEntity->CompPtr<_CompT>(); }

		// Returns a required component. If the component doesn't exist creates it
		template <class _CompT>
		_CompT& CompReq() { return mEntity->CompReq<_CompT>(); }

		void SetEntity(Entity* e);
		Entity* GetEntity() const { return mEntity; }
		virtual void Init();

	private:
		Entity* mEntity;
	};
}