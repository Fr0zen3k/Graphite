//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_GRLOG_H
#define GRAPHITE_GRLOG_H

//engine
#include "core.h"

//vendor
#include "spdlog/spdlog.h"

namespace Graphite {

    /// <summary>
    /// Class that handles all the logging for Graphite, both on the engine and the Sandbox side, using spdlog for all logging
    /// </summary>
    class GRAPHITE_API Log {
    public:
        /// <summary>
        /// Initializes the class and spdlog
        /// </summary>
        static void init();

        /// <summary>
        /// Static getters for the loggers, one instance for the Core, and one for the Sandbox
        /// </summary>
        /// <returns> Return the spdlog::logger type loggers used for logging and debug purposes </returns>
        inline static std::shared_ptr<spdlog::logger> & getCoreLogger() { return m_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> & getClientLogger() { return m_ClientLogger; }

    private:
        /// <summary>
        /// Logger instances
        /// </summary>
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    };

}


/// <summary>
/// Logging macros for different levels of necessity, stripped in release build for memory saving
/// </summary>
#define GR_LOG_TRACE(...)                       ::Graphite::Log::getClientLogger()->trace(__VA_ARGS__)
#define GR_LOG_INFO(...)                        ::Graphite::Log::getClientLogger()->info(__VA_ARGS__)
#define GR_LOG_WARN(...)                        ::Graphite::Log::getClientLogger()->warn(__VA_ARGS__)
#define GR_LOG_ERROR(...)                       ::Graphite::Log::getClientLogger()->error(__VA_ARGS__)
#define GR_LOG_CRITICAL(...)                    ::Graphite::Log::getClientLogger()->critical(__VA_ARGS__)


#define GR_CORE_LOG_TRACE(...)                  ::Graphite::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GR_CORE_LOG_INFO(...)                   ::Graphite::Log::getCoreLogger()->info(__VA_ARGS__)
#define GR_CORE_LOG_WARN(...)                   ::Graphite::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GR_CORE_LOG_ERROR(...)                  ::Graphite::Log::getCoreLogger()->error(__VA_ARGS__)
#define GR_CORE_LOG_CRITICAL(...)               ::Graphite::Log::getCoreLogger()->critical(__VA_ARGS__)

#endif //GRAPHITE_GRLOG_H
