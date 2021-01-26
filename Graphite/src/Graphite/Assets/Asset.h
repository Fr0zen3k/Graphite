//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ASSET_H
#define GRAPHITE_ASSET_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"


namespace Graphite
{
	class GRAPHITE_API Asset
	{
	public:
		Asset(bool needsBinary) : mLoaded(false), mNeedsBinary(needsBinary) {};
		virtual ~Asset() {};


		bool NeedsBinary() const { return mNeedsBinary; }
		bool IsLoaded() const { return mLoaded; }
		virtual void Load(std::istream& source) = 0;
		virtual void Unload() = 0;

	protected:
		bool mLoaded;
		bool mNeedsBinary;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif