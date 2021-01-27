//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ENTITY_H
#define GRAPHITE_ENTITY_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

namespace Graphite
{
	class Component;
	class Scene;

	class GRAPHITE_API Entity
	{
	public:
		Entity(const std::vector<Component*>& components, Scene* scene, const std::string& name);
		virtual ~Entity();

		// Returns the name of this object
		std::string GetName() const { return mName; }

		// Returns the scene this object belongs to
		Scene* GetScene() const { return mScenePtr; }

		// Returns a map of std::type_info* - Component* pairs
		const std::map<const std::type_info*, std::shared_ptr<Component>>& GetComponents() const { return mComponents; }

		// Returns a component. If the component doesn't exist throws std::out_of_range
		template <class _CompT>
		_CompT& Comp() const
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
		_CompT* CompPtr() const
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "The template arg is not a Component");

			auto it = mComponents.find(&typeid(_CompT));

			if (it == mComponents.end())
				return nullptr;
			else
				return (_CompT*)it->second.get();
		}

		// Returns a required component. If the component doesn't exist creates it
		template <class _CompT>
		_CompT& CompReq()
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "The template arg is not a Component");

			auto it = mComponents.find(&typeid(_CompT));

			if (it == mComponents.end())
			{
				_CompT *compPtr = new _CompT();

				// insert comp
				it = mComponents.insert(
					{
						&typeid(_CompT),
						std::shared_ptr<Component>(compPtr)
					}
				).first;

				initNewComp(compPtr);

				return *((_CompT*)it->second.get());
			}
			else
				return *((_CompT*)it->second.get());

			return *static_cast<_CompT*>(
				mComponents.at(
					&typeid(_CompT)
				).get()
				);
		}

	private:
		std::map<const std::type_info*, std::shared_ptr<Component>> mComponents;
		std::string mName;
		Scene* mScenePtr;

		void initNewComp(Component* c);
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif