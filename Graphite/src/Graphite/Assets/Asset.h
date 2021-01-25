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
		Asset(bool needsBinary) : mLoaded(false), mNeedsBinary(needsBinary) {};
		virtual ~Asset() = 0;


		bool NeedsBinary() const { return mNeedsBinary; }
		bool IsLoaded() const { return mLoaded; }
		virtual void Load(std::istream& source) = 0;
		virtual void Unload() = 0;

	protected:
		bool mLoaded;
		bool mNeedsBinary;
	};

}