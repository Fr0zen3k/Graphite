#include "TextureAsset.h"
#include "Graphite/Renderer/RendererCore/Texture.h"

namespace Graphite
{
	TextureAsset::TextureAsset()
	{
	}

	TextureAsset::~TextureAsset()
	{
	}

	void TextureAsset::Load(std::istream& source)
	{
		mInternalTexture = Texture::CreateTexture(source);
	}

	void TextureAsset::Unload()
	{
	}
}