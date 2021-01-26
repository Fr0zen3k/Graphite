#include "Graphite/Core/grpch.h"
#include "Scene2D.h"
#include "Node2DComponent.h"

namespace Graphite
{
	Scene2D::Scene2D()
	{
		CreateEntity({new Node2DComponent()}, "RootNode");
	}

	Scene2D::~Scene2D()
	{
	}

	void Scene2D::Update(float sElapsed)
	{
		for (auto visC : mVisibles)
		{
			visC->Update(sElapsed);
		}
	}

	Node2DComponent* Scene2D::GetRootNode()
	{
		return GetEntity("RootNode")->CompPtr<Node2DComponent>();
	}


	void Scene2D::onComponentAdded(Component* c)
	{
		if (auto visC = dynamic_cast<Visible2DComponent*>(c))
		{
			mVisibles.insert(visC);
		}
	}

	void Scene2D::onComponentRemoved(Component* c)
	{
		if (auto visC = dynamic_cast<Visible2DComponent*>(c))
		{
			mVisibles.erase(visC);
		}
	}
}