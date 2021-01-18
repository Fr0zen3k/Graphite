#include "Visible2DComponent.h"
#include "Node2DComponent.h"
#include "Graphite/Assets/Animation2DAsset.h"

namespace Graphite
{
	Visible2DComponent::Visible2DComponent(AssetPtr<Animation2DAsset> animPtr):
		mAnimationPtr(animPtr)
	{
	}

	Visible2DComponent::Visible2DComponent(const rapidjson::Value& params)
	{
		std::string name = params["animation"].GetString();
		mAnimationPtr = AssetManager::instance().GetAnimation(name);
		if (!mAnimationPtr->IsLoaded())
			AssetManager::instance().LoadAsset(name);
	}

	Visible2DComponent::~Visible2DComponent()
	{
	}

	void Visible2DComponent::SetAnimation(AssetPtr<Animation2DAsset> animPtr)
	{
		mAnimationPtr = animPtr;

		if (mAnimationPtr.isValid())
		{
			double w = mAnimationPtr->GetFrame(0).GetWidth();
			double h = mAnimationPtr->GetFrame(0).GetHeight();

			mNodePtr->AssignBounds({ glm::vec2(-w / 2, -h / 2), glm::vec2(w / 2, h / 2) });
		}
		else
		{
			mNodePtr->AssignBounds({ glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.0) });
		}
	}

	void Visible2DComponent::Init()
	{
		mNodePtr = &CompReq<Node2DComponent>();
		SetAnimation(mAnimationPtr);
	}
}