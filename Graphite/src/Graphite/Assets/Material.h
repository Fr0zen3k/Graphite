#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_MATERIAL_H
#define GRAPHITE_MATERIAL_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

namespace Graphite
{

	class GRAPHITE_API Material
	{
	public:
		Material() = default;
		Material(const glm::vec3& ambient, const glm::vec3& specular, const glm::vec3& light, float ka = 1.0f, float kd = 1.0f, float ks = 1.0f, float shininess = 5.0f);
		Material(float ka, float kd, float ks, float shininess);
		virtual ~Material() = default;

		std::vector<float> GetData(const glm::mat4& modelView) const;

		inline void SetAmbientReflection(float ka) { m_Ka = ka; }
		inline void SetDiffuseReflection(float kd) { m_Kd = kd; }
		inline void SetSpecularReflection(float ks) { m_Ks = ks; }
		inline void Setshininess(float shininess) { m_Shininess = shininess; }

		inline void SetAmbientColor(const glm::vec3& color) { m_AmbientColor = color; }
		inline void SetSpecularColor(const glm::vec3& color) { m_SpecularColor = color; }
		inline void SetRelativeLightPosition(const glm::vec3& lightPosition) { m_LightPosition = lightPosition; }
		
	private:
		glm::vec3 m_AmbientColor = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_SpecularColor = {1.0f, 1.0f, 1.0f};
		glm::vec3 m_LightPosition = {0.0f, 2.0f, 0.0f};		// Relative to the model

		float m_Ka = 1.0f;
		float m_Kd = 1.0f;
		float m_Ks = 1.0f;
		float m_Shininess = 5.0f;
	};
	
}


#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif