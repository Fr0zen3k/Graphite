#include "Node2DComponent.h"
#include "Graphite/Scene/Scene.h"

#include "glm/gtc/type_ptr.hpp"

namespace Graphite
{
	Bounds2D operator*(const glm::mat4x4& transform, const Bounds2D& source)
	{
		glm::vec4 topLeft3D(source.topLeft.x, source.topLeft.y, 0.0, 0.0);
		glm::vec4 bottomRight3D(source.bottomRight.x, source.bottomRight.y, 0.0, 0.0);
		topLeft3D = transform * topLeft3D;
		bottomRight3D = transform * bottomRight3D;

		return Bounds2D{
			glm::vec2(
				std::min(topLeft3D.x, bottomRight3D.x),
				std::min(topLeft3D.y, bottomRight3D.y)
			),
			glm::vec2(
				std::max(topLeft3D.x, bottomRight3D.x),
				std::max(topLeft3D.y, bottomRight3D.y)
			)
		};
	}

	Node2DComponent::Node2DComponent(
		Node2DComponent* parent,
		glm::vec2 position,
		float rotation,
		glm::vec2 scaling
	):
		mParent(nullptr),// it will be set in definition
		mPosition(position),
		mRotation(rotation),
		mScaling(scaling),
		mAssignedBounds{ glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.0) },
		mNeedsUpdate(false)// invalidate will set this to true
	{
		Invalidate();
		SetParent(parent);
	}

	Node2DComponent::Node2DComponent(const rapidjson::Value& params, Scene* scene)
		: Node2DComponent(
			scene->GetEntity(params["parent"].GetString())->CompPtr<Node2DComponent>(),
			glm::vec2(params["position"][0].GetFloat(), params["position"][1].GetFloat()),
			params["rotation"].GetFloat(),
			glm::vec2(params["scaling"][0].GetFloat(), params["scaling"][1].GetFloat())
		)
	{
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

	void Node2DComponent::Move(glm::vec2 shift)
	{
		mPosition += shift;
		Invalidate();
	}

	void Node2DComponent::Rotate(float radians)
	{
		mRotation += radians;
		Invalidate();
	}

	void Node2DComponent::RotateDegrees(float degrees)
	{
		RotateDegrees(glm::radians(degrees));
	}

	void Node2DComponent::Scale(glm::vec2 scaling)
	{
		mScaling.x *= scaling.x;
		mScaling.y *= scaling.y;
		Invalidate();
	}

	void Node2DComponent::AssignBounds(Bounds2D bounds)
	{
		mAssignedBounds = bounds;
		Invalidate();
	}

	void Node2DComponent::update()
	{
		// calculate new transformation

		/*glm::mat4x4 tr = glm::transpose(glm::make_mat3x3(// translate
			{
				1.0f, 0.0f, mPosition.x,
				0.0f, 1.0f, mPosition.y,
				0.0f, 0.0f, 1.0f
			}
		));
		glm::mat4x4 rot = glm::transpose(glm::make_mat3x3(// rotate
			{
				glm::cos(mRotation), -glm::sin(mRotation), 0.0f,
				glm::sin(mRotation), glm::cos(mRotation),  0.0f,
				0.0f,                0.0f,                 1.0f
			}
		));
		glm::mat4x4 sc = glm::transpose(glm::make_mat3x3(// scale
			{
				mScaling.x, 0.0f,       0.0f,
				0.0f,       mScaling.y, 0.0f,
				0.0f,       0.0f,       1.0f
			}
		));
		glm::mat4x4 m = tr*rot*sc;*/
		glm::mat4x4 m = glm::mat4x4(1.0f);
		glm::scale(m, { mScaling.x , mScaling.y, 1.0f });
		glm::rotate(m, mRotation, {0, 0, 1});
		glm::translate(m, { mPosition.x , mPosition.y, 1.0f });

		glm::mat4x4 oldAbsTransform = mAbsTransform;
		if (mParent)
		{
			mAbsTransform = mParent->mAbsTransform * m;
		}
		else
		{
			mAbsTransform = m;
		}

		// update children
		mGraphBounds = mAbsTransform * mAssignedBounds;
		if (mAbsTransform != oldAbsTransform)
		{
			for (auto child : mChildren)
			{
				child->update();
				if (child->mGraphBounds.topLeft != child->mGraphBounds.bottomRight)
				{
					if (mGraphBounds.topLeft == mGraphBounds.bottomRight)
						mGraphBounds = child->mGraphBounds;
					else
					{
						mGraphBounds.topLeft.x = std::min(
							mGraphBounds.topLeft.x, child->mGraphBounds.topLeft.x
						);
						mGraphBounds.topLeft.y = std::min(
							mGraphBounds.topLeft.y, child->mGraphBounds.topLeft.y
						);
						mGraphBounds.bottomRight.x = std::max(
							mGraphBounds.bottomRight.x, child->mGraphBounds.bottomRight.x
						);
						mGraphBounds.bottomRight.y = std::max(
							mGraphBounds.bottomRight.y, child->mGraphBounds.bottomRight.y
						);
					}
				}
			}
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