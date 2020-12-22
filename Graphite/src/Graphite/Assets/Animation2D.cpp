#include "Animation.h"
#include "AssetManager.h"
#include "Texture.h"

namespace Graphite
{
	Frame2D::Frame2D(const Texture* tex, glm::vec2 topLeft, glm::vec2 bottomRight, float w, float h)
		: mTexturePtr(tex)
		, mTopLeft(topLeft)
		, mBottomRight(bottomRight)
		, mWidth(w)
		, mHeight(h)
	{
	}
	Frame2D::~Frame2D()
	{
	}

	Animation2D::Animation2D()
	{
	}
	Animation2D::~Animation2D()
	{
	}
	void Animation2D::Load(const rapidjson::Value& params)
	{
		Texture* tex = AssetManager::instance().GetTexture(params["texture"]);
		glm::vec2 topLeft = glm::vec2(params["area"][0].GetFloat(), params["area"][1].GetFloat());
		glm::vec2 bottomRight = glm::vec2(params["area"][2].GetFloat(), params["area"][3].GetFloat());
		float rows = params["rows"];
		float columns = params["columns"];
		float first = params["frame-first"];
		float last = params["frame-last"];

		glm::vec2 frameSize = bottomRight - topLeft;

		for (int ind = first; ind <= last; ind++)
		{
			int frameX = ind % columns;
			int frameY = ind / columns;
			glm::vec2 pos = topLeft + glm::vec2(frameSize.x * frameX, frameSize.y * frameY);

			mFrames.push_back(Frame2D(
				tex,
				pos, pos + frameSize, 
				tex->GetOriginalWidth() * frameSize.x,
				tex->GetOriginalHeight() * frameSize.y
				)
			);
		}
	}
}