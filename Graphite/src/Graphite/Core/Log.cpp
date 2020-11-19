//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Graphite {

    std::shared_ptr<spdlog::logger> Log::m_CoreLogger = spdlog::stdout_color_mt("GRAPHITE");
    std::shared_ptr<spdlog::logger> Log::m_ClientLogger = spdlog::stdout_color_mt("CLIENT APP");

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");  //change or expand later maybe?

        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger->set_level(spdlog::level::trace);
    }

}
