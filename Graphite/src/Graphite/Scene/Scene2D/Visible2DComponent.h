//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "../Component.h"
#include "Graphite/Assets/AssetManager.h"
//#include "AbstractCollider2DComponent.h"

#include "glm/glm.hpp"

namespace Graphite
{
	class Animation2DAsset;
	class Node2DComponent;

	class GRAPHITE_API Visible2DComponent : public Component
	{
	public:
		Visible2DComponent(AssetPtr<Animation2DAsset> animPtr = AssetPtr<Animation2DAsset>());
		Visible2DComponent(const rapidjson::Value& params);
		~Visible2DComponent();

		void SetAnimation(AssetPtr<Animation2DAsset> animPtr);
		inline AssetPtr<Animation2DAsset> GetAnimation() const { return mAnimationPtr; }

		void Init();


	protected:
		AssetPtr<Animation2DAsset> mAnimationPtr;
		Node2DComponent* mNodePtr;
	};

}