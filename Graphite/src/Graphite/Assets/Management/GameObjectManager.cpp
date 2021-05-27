#include "Graphite/Core/grpch.h"
#include "GameObjectManager.h"

namespace Graphite
{
	std::vector<GameObject*> GameObjectManager::s_GameObjects;
	
	void GameObjectManager::Init()
	{
		s_GameObjects.emplace_back(nullptr);
	}

	void GameObjectManager::Shutdown()
	{
		for(int i = 0; i < s_GameObjects.size(); i++)
		{
			delete s_GameObjects[i];
		}
	}

	GameObjectID GameObjectManager::AddGameObject(const std::string& meshPath)
	{
		GameObject* object = new GameObject(meshPath);

		s_GameObjects.emplace_back(object);

		return s_GameObjects.size() - 1;
	}
}
