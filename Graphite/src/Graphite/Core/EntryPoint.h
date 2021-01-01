//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ENTRYPOINT_H
#define GRAPHITE_ENTRYPOINT_H

#ifdef GR_PLATFORM_WINDOWS
//for later cross-platform purposes, not yet implemented
#endif

#include "Application.h"
#include "Log.h"
#include "Graphite/Renderer/Renderer2D/Renderer2D.h"

/// <summary>
/// The extern function defined by the Sandbox, used to retrieve a client specified instance of an Application
/// </summary>
/// <returns> Returns a pointer to a client made Application instance </returns>
extern Graphite::Application * Graphite::CreateApp();

/// <summary>
/// The main function specifying the game loop in the main thread, runs the Sandbox specified Application.Run()
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char *argv[]) {

    Graphite::Log::init();

    GR_CORE_LOG_WARN("Core logger init");
    GR_LOG_CRITICAL("Client app logger init");

    Graphite::Application *userApp = Graphite::CreateApp();
    userApp->run();
    delete userApp;

    return 0;
}

#endif //GRAPHITE_ENTRYPOINT_H
