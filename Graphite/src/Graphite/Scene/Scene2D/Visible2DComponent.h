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
		void Update(float sElapsed);

		void SetAnimationFPS(float fps);
		float GetAnimationFPS() const { return mAnimFPS; }
		void SetFrameIndex(float index);
		float GetFrameIndex() const { return mFrameInd; }
		Frame2D& GetCurrentFrame() const;


	protected:
		AssetPtr<Animation2DAsset> mAnimationPtr;
		Node2DComponent* mNodePtr;

		float mFrameInd;
		float mAnimFPS;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif