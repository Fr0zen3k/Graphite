//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

#include "Asset.h"

namespace Graphite
{
	class GRAPHITE_API Texture : public Asset
	{
	public:
		Texture();
		~Texture();

		int GetOriginalWidth() const;
		int GetOriginalHeight() const;

	protected:
	};

}