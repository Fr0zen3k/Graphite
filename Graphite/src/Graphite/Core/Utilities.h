#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "grpch.h"

#ifndef GRAPHITE_GENERAL_UTILITIES_H
#define GRAPHITE_GENERAL_UTILITIES_H

namespace Graphite
{

	namespace Datamanip
	{

		inline static std::vector<std::string> SplitPath(const std::string& path)
		{
			std::vector<std::string> res(0);

			std::stringstream ss;
			
			for(char c : path)
			{
				if((c == '\\' || c == '/') && ss.str() != "")
				{
					res.emplace_back(ss.str());
					ss.str("");
				}
				else
				{
					ss << c;
				}
			}

			return res;
		}
		
	}
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif