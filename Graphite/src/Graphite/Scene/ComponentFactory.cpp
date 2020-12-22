#include "ComponentFactory.h"

namespace Graphite
{
	Component* ComponentFactory::GetNewComponent(const rapidjson::Value& obj)
	{
		auto it = mConstructorsPerType.find(obj["type"].GetString());

		if (it == mConstructorsPerType.end())
		{
			throw std::invalid_argument(std::string("No Component constructor for type '") + typeName + "'");
		}

		return mConstructorsPerType[typeName](obj);
	}

	void ComponentFactory::RegisterConstructor(const std::string& typeName, ComponentConstructor ctor)
	{
		mConstructorsPerType[typeName] = ctor;
	}
}