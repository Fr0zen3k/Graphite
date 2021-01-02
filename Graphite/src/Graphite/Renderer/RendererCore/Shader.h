#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_SHADER_H
#define GRAPHITE_SHADER_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Utilities.h"

namespace Graphite
{

	class GRAPHITE_API Shader
	{
	public:
		virtual ShaderType GetShaderType() const = 0;
		virtual void SetShaderFilepath(const std::string& filepath) = 0;
		virtual void SetShaderType(ShaderType type) = 0;

		static Shader* CreateShader();
		static Shader* CreateShader(ShaderType type);
		static Shader* CreateShader(ShaderType type, const std::string& filepath);
		
	protected:
		Shader() = default;
		virtual ~Shader() = default;
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif