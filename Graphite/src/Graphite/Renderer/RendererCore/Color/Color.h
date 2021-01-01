#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_COLOR_H
#define GRAPHITE_COLOR_H

#include "glm/glm.hpp"

namespace Graphite
{

	/// <summary>
	/// Enum class used to declare the color layout to be used by the class when returning a vec4
	/// </summary>
	enum class grColorLayout
	{
		GR_RGBA,
		GR_RBGA,
		GR_RGAB,
		GR_RBAG,
		GR_RABG,
		GR_RAGB,
		GR_GRBA,
		GR_GBRA,
		GR_GRAB,
		GR_GBAR,
		GR_GABR,
		GR_GARB,
		GR_BRGA,
		GR_BGRA,
		GR_BRAG,
		GR_BGAR,
		GR_BAGR,
		GR_BARG,
		GR_ARBG,
		GR_ABRG,
		GR_ARGB,
		GR_ABGR,
		GR_AGBR,
		GR_AGRB,
	};

	/// <summary>
	/// Primitive types to use for storing raw color data when declaring a variable
	/// If some other type is used when declaring a variable, the color raw data may not have the appropriate size or sign to use with Vulkan API
	/// A color declaration will be defined automatically within the renderer that will be available for use with the renderer on a certain platform or device
	/// </summary>
	typedef uint8_t				GR_COLOR_SIZE_8_BIT;
	typedef uint16_t			GR_COLOR_SIZE_16_BIT;
	typedef uint32_t			GR_COLOR_SIZE_32_BIT;

	/// <summary>
	/// Class to use as an interface with the renderer, when rendering objects with solid color, or for color calculations
	/// The class is made with possibility to specify the size and layout, in order to be compatible with the Vulkan API
	/// The color class of appropriate size and layout for the device will be defined within the Graphite renderer
	/// </summary>
	/// <typeparam name="_GR_COLOR_SIZE"> The parameter that specifies the variable type to use for raw data storage.
	/// Supported: GR_COLOR_SIZE_8_BIT (uint8_t), GR_COLOR_SIZE_16_BIT (uint16_t) and GR_COLOR_SIZE_32_BIT (uint32_t)
	/// A type of numeric nature must be used, otherwise the class might not function
	/// If not using the official supported types, the class will not be compatible with the renderer and Vulkan API, therefore unusable for rendering purposes, only computation
	/// </typeparam>
	template<typename _GR_COLOR_SIZE, grColorLayout _GR_COLOR_LAYOUT> class GRAPHITE_API Color
	{
		
	public:
		/// <summary>
		/// Constructors:
		/// The empty constructor initializes a color with all values of raw data set to 0
		/// The class allows construction of colors with either rgba values, or percentages, if the percentages pass the bounds of [0.0f, 1.0f], the values are se to minimum/maximum
		/// If a class is initialized with percentages, the raw data contained within will still be in the _GR_COLOR_SIZE format, not percentage/float format
		/// </summary>
		/// <param name="red"> Raw data for the red value either in integer or float format </param>
		/// <param name="green"> Raw data for the green value either in integer or float format </param>
		/// <param name="blue"> Raw data for the blue value either in integer or float format </param>
		/// <param name="alpha"> Raw data for the alpha value either in integer or float format </param>
		Color();
		Color(_GR_COLOR_SIZE red, _GR_COLOR_SIZE green, _GR_COLOR_SIZE blue, _GR_COLOR_SIZE alpha);
		Color(float red, float green, float blue, float alpha);

		/// <summary>
		/// glm::vec4 format for use with the renderer and the Vulkan API
		/// </summary>
		/// <returns> Returns a glm::vec4 with all the color data in format for use with the renderer </returns>
		glm::vec4 GetColorPercentageVector();

		/// <summary>
		/// Getters for raw values and percentages of the color
		/// </summary>
		/// <returns> Raw values and percentages for the values of certain parts of the color </returns>
		inline _GR_COLOR_SIZE GetRed() { return m_Red; }
		inline float GetRedPercentage()
		{
			std::numeric_limits<_GR_COLOR_SIZE> limit;
			return (float)m_Red / limit.max();
		}
		inline _GR_COLOR_SIZE GetGreen() { return m_Green; }
		inline float GetGreenPrecentage()
		{
			std::numeric_limits<_GR_COLOR_SIZE> limit;
			return (float)m_Green / limit.max();
		}
		inline _GR_COLOR_SIZE GetBlue() { return m_Blue; }
		inline float GetBluePercentage()
		{
			std::numeric_limits<_GR_COLOR_SIZE> limit;
			return (float)m_Blue / limit.max();
		}
		inline _GR_COLOR_SIZE GetAlpha() { return m_Alpha; }
		inline float GetAlphaPercentage()
		{
			std::numeric_limits<_GR_COLOR_SIZE> limit;
			return (float)m_Alpha / limit.max();
		}

		/// <summary>
		/// Operator for color blending, keeps the bigger alpha value, and mixes the rest according to the alpha value of the right(top) color
		/// </summary>
		/// <param name="topColor"> The top of the two colors</param>
		/// <returns></returns>
		Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT> operator + (Color<_GR_COLOR_SIZE, _GR_COLOR_LAYOUT> topColor);
		
	private:
		/// <summary>
		/// Private variables containing the raw data of the color
		/// </summary>
		_GR_COLOR_SIZE m_Red;
		_GR_COLOR_SIZE m_Green;
		_GR_COLOR_SIZE m_Blue;
		_GR_COLOR_SIZE m_Alpha;
	};
	
}

#endif
