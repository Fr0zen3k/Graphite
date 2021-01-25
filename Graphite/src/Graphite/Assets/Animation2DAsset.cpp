#include "Animation2DAsset.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "Animation2DAsset.h"

namespace Graphite
{
	Frame2D::Frame2D(AssetPtr<const TextureAsset> tex, glm::vec2 topLeft, glm::vec2 bottomRight, float w, float h)
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

	Animation2DAsset::Animation2DAsset() :
		Asset(false)
	{
	}

	Animation2DAsset::~Animation2DAsset()
	{
	}

	void Animation2DAsset::Load(std::istream& source)
	{
		rapidjson::Document d;
		d.ParseStream(source);

		Load(d);
	}

	void Animation2DAsset::Load(const rapidjson::Value& params)
	{
		AssetPtr<TextureAsset> tex = AssetManager::instance().GetTexture(params["texture"].GetString());
		glm::vec2 topLeft = glm::vec2(params["area"][0].GetFloat(), params["area"][1].GetFloat());
		glm::vec2 bottomRight = glm::vec2(params["area"][2].GetFloat(), params["area"][3].GetFloat());
		int rows = params["rows"].GetInt();
		int columns = params["columns"].GetInt();
		int first = params["frame-first"].GetInt();
		int last = params["frame-last"].GetInt();

		glm::vec2 sheetSize = bottomRight - topLeft;
		glm::vec2 frameSize(sheetSize.x / columns, sheetSize.y / rows);

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
	void Animation2DAsset::Unload()
	{
	}
}