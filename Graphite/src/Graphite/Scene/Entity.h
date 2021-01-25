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

#include "Scene.h"

#include "Component.h"

namespace Graphite
{
	class Component;

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
		const std::map<const std::type_info*, std::unique_ptr<Component>>& GetComponents() const { return mComponents; }

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

			std::map<std::type_info*, std::unique_ptr<Component>>::iterator it = mComponents.find(&typeid(_CompT));

			if (it == mComponents.end())
				return nullptr;
			else
				return it->second.get();
		}

		// Returns a required component. If the component doesn't exist creates it
		template <class _CompT>
		_CompT& CompReq()
		{
			static_assert(std::is_base_of<Component, _CompT>::value, "The template arg is not a Component");

			std::map<std::type_info*, std::unique_ptr<Component>>::iterator it = mComponents.find(&typeid(_CompT));

			if (it == mComponents.end())
			{
				// insert comp
				it = mComponents.insert(
					{
						&typeid(_CompT),
						std::unique_ptr<Component>(compCont.componentPtr())
					}
				).first;

				// init comp
				it->second->SetEntity(this);
				it->second->Init();

				// notify scene
				if (mScene)
					mScene->onComponentAdded(it->second);

				return *(it->second);
			}
			else
				return *it->second;

			return *static_cast<_CompT*>(
				mComponents.at(
					&typeid(_CompT)
				).get()
				);
		}

	private:
		std::map<const std::type_info*, std::unique_ptr<Component>> mComponents;
		std::string mName;
		Scene* mScenePtr;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif