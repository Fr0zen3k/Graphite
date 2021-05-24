#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_TEXTUREMANAGER_H
#define GRAPHITE_TEXTUREMANAGER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Graphite/Renderer/RendererCore/Texture.h"

namespace Graphite {

	class GRAPHITE_API TextureManager
	{
	public:
		static void Init();
		static void Shutdown();
		
		inline static Texture* GetTexture(TextureID texture) { return s_Textures[texture].texture; }
		
		static TextureID AddTexture(const std::string& path);

	private:
		struct TextureContainer
		{
			Texture* texture = nullptr;
			std::string path = "";
		};

		static std::vector<TextureContainer> s_Textures;
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif