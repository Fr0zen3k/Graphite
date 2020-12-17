#pragma once

#include "Graphite/Core/grpch.h"

#include "../Component.h"
#include "Bounds2D.h"

#include "glm/glm.hpp"

#include <set>

namespace Graphite
{

	class Node2DComponent : Component
	{
	public:
		Node2DComponent(
			Entity* entity,
			Node2DComponent* parent,
			glm::vec2 position = glm::vec2(0.0f, 0.0f),
			float rotation = 0.0f, 
			glm::vec2 scaling = glm::vec2(1.0f, 1.0f)
		);
		Node2DComponent() = delete;

		~Node2DComponent();

		inline Node2DComponent* GetParent() const { return mParent; }
		inline const std::set<Node2DComponent*>& GetChildren() const { return mChildren; }

		inline glm::vec2 GetPosition() const { return mPosition; }
		inline float GetRotation() const { return mRotation; }
		inline float GetRotationDegrees() const { return glm::degrees(mRotation); }
		inline glm::vec2 GetScaling() const { return mScaling; }

		inline glm::mat3x3 GetAbsoluteTransformation() const { return mAbsTransform; }
		inline bool NeedsUpdate() const { return mNeedsUpdate; }

		void SetParent(Node2DComponent* parent);

		void SetPosition(glm::vec2 position);
		void SetRotation(float radians);
		void SetRotationDegrees(float degrees);
		void SetScaling(glm::vec2 scaling);

		void update();

	protected:
		Node2DComponent* mParent;
		std::set<Node2DComponent*> mChildren;

		glm::vec2 mPosition;
		float mRotation;
		glm::vec2 mScaling;

		glm::mat3x3 mAbsTransform;
		bool mNeedsUpdate;

		// Marks for updating
		void Invalidate();
		void InvalidateParent();
	};

}