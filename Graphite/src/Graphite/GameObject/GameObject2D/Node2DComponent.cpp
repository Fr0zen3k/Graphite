#include "Node2DComponent.h"

#include "glm/gtc/type_ptr.hpp"

namespace Graphite
{

	Node2DComponent::Node2DComponent(
		Entity* entity,
		Node2DComponent* parent,
		glm::vec2 position,
		float rotation,
		glm::vec2 scaling
	):
		Component(entity),
		mParent(nullptr),// it will be set in definition
		mPosition(position),
		mRotation(rotation),
		mScaling(scaling),
		mNeedsUpdate(false)// invalidate will set this to true
	{
		Invalidate();
		SetParent(parent);
	}

	Node2DComponent::~Node2DComponent()
	{
		SetParent(nullptr);
	}

	void Node2DComponent::SetParent(Node2DComponent* parent)
	{
		if (mParent)
		{
			mParent->mChildren.erase(this);
			InvalidateParent();
		}

		mParent = parent;

		if (mParent)
			mParent->mChildren.insert(this);

		Invalidate();
	}

	void Node2DComponent::SetPosition(glm::vec2 position)
	{
		mPosition = position;
		Invalidate();
	}

	void Node2DComponent::SetRotation(float radians)
	{
		mRotation = radians;
		Invalidate();
	}

	void Node2DComponent::SetRotationDegrees(float degrees)
	{
		SetRotation(glm::radians(degrees));
	}

	void Node2DComponent::SetScaling(glm::vec2 scaling)
	{
		mScaling = scaling;
		Invalidate();
	}

	void Node2DComponent::update()
	{
		// calculate new transformation

		glm::mat3x3 tr = glm::transpose(glm::make_mat3x3(// translate
			{
				1.0f, 0.0f, mPosition.x,
				0.0f, 1.0f, mPosition.y,
				0.0f, 0.0f, 1.0f
			}
		));
		glm::mat3x3 rot = glm::transpose(glm::make_mat3x3(// rotate
			{
				glm::cos(mRotation), -glm::sin(mRotation), 0.0f,
				glm::sin(mRotation), glm::cos(mRotation),  0.0f,
				0.0f,                0.0f,                 1.0f
			}
		));
		glm::mat3x3 sc = glm::transpose(glm::make_mat3x3(// scale
			{
				mScaling.x, 0.0f,       0.0f,
				0.0f,       mScaling.y, 0.0f,
				0.0f,       0.0f,       1.0f
			}
		));
		glm::mat3x3 m = tr*rot*sc;
		
		if (mParent)
		{
			mAbsTransform = mParent->mAbsTransform * m;
		}
		else
		{
			mAbsTransform = m;
		}

		// update children
		for (auto child : mChildren)
		{
			if (child->mNeedsUpdate)
				child->update();
		}

		//TODO: bounding boxes

		// unmark for update
		mNeedsUpdate = false;
	}

	void Node2DComponent::Invalidate()
	{
		mNeedsUpdate = true;
		InvalidateParent();
	}

	void Node2DComponent::InvalidateParent()
	{
		Node2DComponent* cur = this->mParent;

		while (cur && !cur->mNeedsUpdate)
		{
			cur->mNeedsUpdate = true;
			cur = cur->mParent;
		}
	}

}