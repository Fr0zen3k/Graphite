#include "Graphite/Core/grpch.h"
#include "ColliderRectComponent.h"

namespace Graphite
{
	ColliderRectComponent::ColliderRectComponent(float width, float height)
		: mWidth(width)
		, mHeight(height)
	{
	}

	ColliderRectComponent::ColliderRectComponent(const rapidjson::Value& params)
		: ColliderRectComponent(params["width"].GetFloat(), params["height"].GetFloat())
	{
	}

	ColliderRectComponent::~ColliderRectComponent()
	{
	}

	std::array<glm::vec2, 4> ColliderRectComponent::GetTransformedVertices(const glm::mat4x4& transform)
	{
		glm::vec4 vecArray3DAffine[4] =
		{
			transform * glm::vec4(-mWidth / 2, -mHeight / 2, 0.0f, 1.0f),
			transform * glm::vec4(mWidth / 2, -mHeight / 2, 0.0f, 1.0f),
			transform * glm::vec4(mWidth / 2, mHeight / 2, 0.0f, 1.0f),
			transform * glm::vec4(-mWidth / 2, mHeight / 2, 0.0f, 1.0f)
		};

		return std::array<glm::vec2, 4>(
			{
				glm::vec2(vecArray3DAffine[0].x, vecArray3DAffine[0].y),
				glm::vec2(vecArray3DAffine[1].x, vecArray3DAffine[1].y),
				glm::vec2(vecArray3DAffine[2].x, vecArray3DAffine[2].y),
				glm::vec2(vecArray3DAffine[3].x, vecArray3DAffine[3].y),
			}
		);
	}
}