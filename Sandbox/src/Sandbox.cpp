//
// Created by Jan Kresic on 9/19/20.
//
#include "Graphite/Core/grpch.h"
#include "Graphite.h"

class Sandbox : public Graphite::Application {
public:
    Sandbox(): Application() {}

    ~Sandbox() {

    }

	void Start() override
    {
	    // Code run on startup of the application and never again
    	
    }

	void Tick() override
    {
	    // Code run once per frame in the game loop
    	
    }

	void Shutdown() override
    {
	    // Code run on shutdown of the application
    	
    }
};

Graphite::Application* Graphite::CreateApp() {
    return new Sandbox();
}
