#include "Scene2D.h"

namespace Graphite
{
	Scene2D::Scene2D()
	{
	}

	Scene2D::Scene2D(rapidjson::Value root)
		: Scene(root)
	{
	}

	Scene2D::~Scene2D()
	{
	}


	void Scene2D::onComponentAdded(Component* c)
	{
	}

	void onComponentRemoved(Component* c);
	{
	}
}