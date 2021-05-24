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

	std::vector<float> Material::GetData() const
	{
		std::vector<float> data;

		data.emplace_back(m_AmbientColor[0]);
		data.emplace_back(m_AmbientColor[1]);
		data.emplace_back(m_AmbientColor[2]);
		data.emplace_back(m_SpecularColor[0]);
		data.emplace_back(m_SpecularColor[1]);
		data.emplace_back(m_SpecularColor[2]);
		data.emplace_back(m_LightPosition[0]);
		data.emplace_back(m_LightPosition[1]);
		data.emplace_back(m_LightPosition[2]);
		data.emplace_back(m_Ka);
		data.emplace_back(m_Kd);
		data.emplace_back(m_Ks);
		data.emplace_back(m_Shininess);

		return data;
	}
}
