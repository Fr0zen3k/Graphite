#include "Graphite/Core/grpch.h"
#include "TextureManager.h"

namespace Graphite
{
	std::vector<TextureManager::TextureContainer> TextureManager::s_Textures;
	
	void TextureManager::Init()
	{
		TextureContainer c;

		s_Textures.emplace_back(c);
	}

	void TextureManager::Shutdown()
	{
		for(TextureContainer c : s_Textures)
		{
			if(c.texture != nullptr)
			{
				delete c.texture;
			}
		}
	}

	TextureID TextureManager::AddTexture(const std::string& path)
	{
		if(path == "")
		{
			return 0;
		}

		for(int i = 0; i < s_Textures.size(); i++)
		{
			if(s_Textures[i].path == path)
			{
				return i;
			}
		}

		TextureContainer c;
		c.path = path;
		c.texture = Texture::CreateTexture(path);

		s_Textures.emplace_back(c);

		return s_Textures.size() - 1;
	}
}
