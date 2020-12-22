//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

namespace Graphite
{
	class GRAPHITE_API Asset
	{
	public:
		Asset() : mLoaded(false) {};
		virtual ~Asset() = 0;


		bool IsLoaded() { return mLoaded; }
		virtual void Load(std::istream& source) = 0;
		virtual void Unload() = 0;

	protected:
		bool mLoaded;
	};

}