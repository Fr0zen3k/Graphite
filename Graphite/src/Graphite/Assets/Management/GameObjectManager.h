#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_GAMEOBJECTMANAGER_H
#define GRAPHITE_GAMEOBJECTMANAGER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../GameObject.h"

namespace Graphite {

	class GRAPHITE_API GameObjectManager
	{
	public:
		static void Init();
		static void Shutdown();

		inline static GameObject* GetGameObject(GameObjectID gameObject) { return s_GameObjects[gameObject]; }
		
		static GameObjectID AddGameObject(const std::string& meshPath);

		inline static size_t Size() { return s_GameObjects.size(); }
		
	private:
		static std::vector<GameObject*> s_GameObjects;
	};

}

#endif


#if defined (_MSC_VER)
#pragma warning(pop)
#endif