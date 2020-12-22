//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

namespace Graphite
{
	class Component;

	class ComponentFactory
	{
	public:
		using ComponentConstructor = std::function<Component* (const rapidjson::Value&)>;

		// Creates a new component from the json object.
		// A constructor for the specified 'type' must be registered, otherwise invalid_argument exception is thrown.
		Component* GetNewComponent(const rapidjson::Value& obj);

		// Registers the constructor for the specified typeName
		void RegisterConstructor(const std::string& typeName, ComponentConstructor ctor);

	private:
		std::map<std::string, ComponentConstructor > mConstructorsPerType;
	};

}