#include "TextureAsset.h"
#include "Graphite/Renderer/RendererCore/Texture.h"

namespace Graphite
{
	TextureAsset::TextureAsset():
		Asset(true)
	{
	}

	TextureAsset::~TextureAsset()
	{
	}

	void TextureAsset::Load(std::istream& source)
	{
		mInternalTexture = Texture::CreateTexture(source);

		mWidth = mInternalTexture->GetTextureSize().first;
		mHeight = mInternalTexture->GetTextureSize().second;
	}

	void TextureAsset::Unload()
	{
	}
}