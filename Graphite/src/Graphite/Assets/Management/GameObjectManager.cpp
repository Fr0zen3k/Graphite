#include "Graphite/Core/grpch.h"
#include "GameObjectManager.h"

namespace Graphite
{
	std::vector<GameObjectManager::GameObjectContainer> GameObjectManager::s_GameObjects;
	
	void GameObjectManager::Init()
	{
		GameObjectContainer c;
		s_GameObjects.emplace_back(c);
	}

	void GameObjectManager::Shutdown()
	{
		for(int i = 0; i < s_GameObjects.size(); i++)
		{
			if(s_GameObjects[i].gameObject != nullptr)
			{
				delete s_GameObjects[i].gameObject;
			}
		}
	}

	GameObjectID GameObjectManager::AddGameObject(const std::string& path, LOD lod)
	{
		if(path == "")
		{
			return 0;
		}
		
		for(int i = 0; i < s_GameObjects.size(); i++)
		{
			if(s_GameObjects[i].path == path)
			{
				s_GameObjects[i].gameObject->AddLOD(path, lod);
				return i;
			}
		}

		GameObjectContainer c;
		c.path = path;
		c.gameObject = new GameObject(path, lod);

		s_GameObjects.emplace_back(c);

		return s_GameObjects.size() - 1;
	}
}
