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

}
