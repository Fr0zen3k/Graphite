//
// Created by Jan Kresic on 9/19/20.
//

#include <Graphite.h>

class Sandbox : public Graphite::Application {
public:
    Sandbox() {}

    ~Sandbox() {

    }
};

Graphite::Application* Graphite::CreateApp() {
    return new Sandbox();
}
