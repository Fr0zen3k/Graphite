//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ENTRYPOINT_H
#define GRAPHITE_ENTRYPOINT_H

#ifdef GR_PLATFORM_WINDOWS
//for later cross-platform purposes, not yet implemented
#endif

#include "Application.h"
#include "Log.h"
#include "Graphite/Renderer/Renderer3D/Renderer3D.h"
#include "Graphite/Assets/Management/GameObjectManager.h"

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
    srand(time(nullptr));
	
    Graphite::Log::init();

    GR_CORE_LOG_WARN("Core logger init");
    GR_LOG_CRITICAL("Client app logger init");

    Graphite::Application *userApp = Graphite::CreateApp();
	
    Graphite::Renderer3D::Init();
	
    userApp->SetActiveCamera(Graphite::Camera::CreateCamera(Graphite::CameraType::Perspective));

    Graphite::Application::SetAppDir(std::string(argv[0]));
    Graphite::Application::InitBenchmarking();
	
    userApp->GetActiveCameraInstance()->Translate(glm::vec3(0.0f, 0.0f, 15.0f));
	
    Graphite::Renderer3D::InitAPI();

    userApp->Start();
	
    userApp->Run();

    userApp->Shutdown();
	
    delete userApp;

    Graphite::Renderer3D::Shutdown();

    return 0;
}

#endif //GRAPHITE_ENTRYPOINT_H

#if defined (_MSC_VER)
#pragma warning(pop)
#endif