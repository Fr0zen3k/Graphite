#include "Graphite/Core/grpch.h"
#include "Material.h"

namespace Graphite
{
	Material::Material(const glm::vec3& ambient, const glm::vec3& specular, const glm::vec3& light, float ka, float kd, float ks,
		float shininess): m_AmbientColor(ambient), m_SpecularColor(specular), m_LightPosition(light), m_Ka(ka), m_Kd(kd), m_Ks(ks), m_Shininess(shininess)
	{

	}

	Material::Material(float ka, float kd, float ks, float shininess): m_Ka(ka), m_Kd(kd), m_Ks(ks), m_Shininess(shininess)
	{

	}

	std::vector<float> Material::GetData(const glm::mat4& modelView) const
	{
		std::vector<float> data;

		glm::vec4 light = modelView * glm::vec4(m_LightPosition, 1.0f);

		data.emplace_back(m_AmbientColor.x);
		data.emplace_back(m_AmbientColor.y);
		data.emplace_back(m_AmbientColor.z);
		data.emplace_back(m_SpecularColor.x);
		data.emplace_back(m_SpecularColor.y);
		data.emplace_back(m_SpecularColor.z);
		data.emplace_back(light.x / light.w);
		data.emplace_back(light.y / light.w);
		data.emplace_back(light.z / light.w);
		data.emplace_back(m_Ka);
		data.emplace_back(m_Kd);
		data.emplace_back(m_Ks);
		data.emplace_back(m_Shininess);

		return data;
	}
}
