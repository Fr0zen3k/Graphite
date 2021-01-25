//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_COMPONENTFACTORY_H
#define GRAPHITE_COMPONENTFACTORY_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Component.h"

namespace Graphite
{
	class GRAPHITE_API ComponentFactory
	{
	public:
		using ComponentConstructor = std::function<Component* (const rapidjson::Value&, Scene*)>;

		static ComponentFactory& instance();

		// Creates a new component from the json object.
		// A constructor for the specified 'type' must be registered, otherwise invalid_argument exception is thrown.
		Component* GetNewComponent(const rapidjson::Value& obj, Scene* scene);

		// Registers the constructor for the specified typeName
		void RegisterConstructor(const std::string& typeName, ComponentConstructor ctor);

	private:
		std::map<std::string, ComponentConstructor > mConstructorsPerType;

		ComponentFactory();
	};


}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif