//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

#ifndef GRAPHITE_CORE_H
#define GRAPHITE_CORE_H

#ifdef GR_PLATFORM_WINDOWS
    #ifdef GR_BUILD_DLL
        #define GRAPHITE_API __declspec(dllexport)
    #else
        #define GRAPHITE_API __declspec(dllimport)
    #endif
#else
    #define GRAPHITE_API
#endif

#define GR_BIT(x) (1 << x)

#define GR_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1);

#ifdef GR_ENABLE_ASSERT
	#define GR_CORE_ASSERT(x, ...) { if(!(x)) { GR_CORE_LOG_CRITICAL("Assertion Failed With Return Code: {0}", __VA_ARGS__); } }
	#define GR_ASSERT(x, ...) { if(!(x)) { GR_LOG_CRITICAL("Assertion Failed With Return Code: {0}", __VA_ARGS__); } }
#else
	#define GR_CORE_ASSERT(x, ...)
	#define GR_ASSERT(x, ...)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN
	#define GR_GRAPHICS_CONTEXT dynamic_cast<VulkanGraphicsContext*>(Renderer2D::GetGraphicsContext())
#endif


#endif //GRAPHITE_CORE_H
