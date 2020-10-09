//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

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
    class GRAPHITE_API grLog {
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
#define GR_LOG_TRACE(...)                       ::Graphite::grLog::getClientLogger()->trace(__VA_ARGS__)
#define GR_LOG_INFO(...)                        ::Graphite::grLog::getClientLogger()->info(__VA_ARGS__)
#define GR_LOG_WARN(...)                        ::Graphite::grLog::getClientLogger()->warn(__VA_ARGS__)
#define GR_LOG_ERROR(...)                       ::Graphite::grLog::getClientLogger()->error(__VA_ARGS__)
#define GR_LOG_CRITICAL(...)                    ::Graphite::grLog::getClientLogger()->critical(__VA_ARGS__)


#define GR_CORE_LOG_TRACE(...)                  ::Graphite::grLog::getCoreLogger()->trace(__VA_ARGS__)
#define GR_CORE_LOG_INFO(...)                   ::Graphite::grLog::getCoreLogger()->info(__VA_ARGS__)
#define GR_CORE_LOG_WARN(...)                   ::Graphite::grLog::getCoreLogger()->warn(__VA_ARGS__)
#define GR_CORE_LOG_ERROR(...)                  ::Graphite::grLog::getCoreLogger()->error(__VA_ARGS__)
#define GR_CORE_LOG_CRITICAL(...)               ::Graphite::grLog::getCoreLogger()->critical(__VA_ARGS__)

#endif //GRAPHITE_GRLOG_H
