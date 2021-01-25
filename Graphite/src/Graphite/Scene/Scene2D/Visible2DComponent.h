//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_VISIBLE2DCOMPONENT_H
#define GRAPHITE_VISIBLE2DCOMPONENT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Component.h"
#include "Graphite/Assets/AssetManager.h"

#include "Node2DComponent.h"
#include "Graphite/Assets/Animation2DAsset.h"

namespace Graphite
{
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

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif