#include "Graphite/Core/grpch.h"
#include "Color.h"

namespace Graphite
{

	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>::Color() :
		m_Red(0), m_Green(0), m_Blue(0), m_Alpha(0) {}

	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>::
		Color(_GR_COLOR_SIZE red, _GR_COLOR_SIZE green, _GR_COLOR_SIZE blue, _GR_COLOR_SIZE alpha) :
		m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha) {}

	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>::
		Color(float red, float green, float blue, float alpha)
	{
		if (red < 0.0f)
		{
			red = 0.0f;
		}
		else if (red > 1.0f)
		{
			red = 1.0f;
		}
		
		if (blue < 0.0f)
		{
			blue = 0.0f;
		}
		else if (blue > 1.0f)
		{
			blue = 1.0f;
		}
		
		if (green < 0.0f)
		{
			green = 0.0f;
		}
		else if (green > 1.0f)
		{
			green = 1.0f;
		}
		
		if (alpha < 0.0f)
		{
			alpha = 0.0f;
		}
		else if (alpha > 1.0f)
		{
			alpha = 1.0f;
		}

		std::numeric_limits<_GR_COLOR_SIZE> limit;

		m_Red = (_GR_COLOR_SIZE)(limit.max() * red);
		m_Green = (_GR_COLOR_SIZE)(limit.max() * green);
		m_Blue = (_GR_COLOR_SIZE)(limit.max() * blue);
		m_Alpha = (_GR_COLOR_SIZE)(limit.max() * alpha);
	}

	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> glm::vec4 Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>::GetColorPercentageVector()
	{
		glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);


		switch (_GR_COLOR_LAYOUT)
		{
		case(grColorLayout::GR_RGBA):
		{
			res.x = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.z = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_RBGA):
		{
			res.x = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_RGAB):
		{
			res.x = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_RBAG):
		{
			res.x = GetRedPercentage();
			res.w = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_RABG):
		{
			res.x = GetRedPercentage();
			res.w = GetGreenPrecentage();
			res.z = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_RAGB):
		{
			res.x = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GRBA):
		{
			res.y = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.z = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GBRA):
		{
			res.z = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GRAB):
		{
			res.y = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GBAR):
		{
			res.w = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GABR):
		{
			res.w = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.z = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_GARB):
		{
			res.z = GetRedPercentage();
			res.x = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BRGA):
		{
			res.y = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BGRA):
		{
			res.z = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.w = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BRAG):
		{
			res.y = GetRedPercentage();
			res.w = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BGAR):
		{
			res.w = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.z = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BAGR):
		{
			res.w = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_BARG):
		{
			res.z = GetRedPercentage();
			res.w = GetGreenPrecentage();
			res.x = GetBluePercentage();
			res.y = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_ARBG):
		{
			res.y = GetRedPercentage();
			res.w = GetGreenPrecentage();
			res.z = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_ABRG):
		{
			res.z = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_ARGB):
		{
			res.y = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_ABGR):
		{
			res.w = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_AGBR):
		{
			res.w = GetRedPercentage();
			res.z = GetGreenPrecentage();
			res.y = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		case(grColorLayout::GR_AGRB):
		{
			res.z = GetRedPercentage();
			res.y = GetGreenPrecentage();
			res.w = GetBluePercentage();
			res.x = GetAlphaPercentage();
			break;
		}
		default: break;
		}

		return res;
	}

	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>
							Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT>::operator + (Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT> topColor)
	{
		_GR_COLOR_SIZE red;
		_GR_COLOR_SIZE green;
		_GR_COLOR_SIZE blue;
		_GR_COLOR_SIZE alpha;

		alpha = std::max(m_Alpha, topColor.GetAlpha());

		red = static_cast<_GR_COLOR_SIZE>(topColor.GetAlphaPercentage() * m_Red + (1 - topColor.GetAlphaPercentage()) * topColor.GetRed());
		green = static_cast<_GR_COLOR_SIZE>(topColor.GetAlphaPercentage() * m_Green + (1 - topColor.GetAlphaPercentage()) * topColor.GetGreen());
		blue = static_cast<_GR_COLOR_SIZE>(topColor.GetAlphaPercentage() * m_Blue + (1 - topColor.GetAlphaPercentage()) * topColor.GetBlue());

		Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT> res(red, green, blue, alpha);

		return res;
	}
	
}