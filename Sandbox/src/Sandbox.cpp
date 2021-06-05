//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"
#include "Graphite.h"
#include "Graphite/Core/Input.h"


class Sandbox : public Graphite::Application {
public:
    Sandbox(): Application() {}

    ~Sandbox() override {

    }
    
	void Start() override
    {
	    // Code run on startup of the application and never again
        std::string path = GetAppDir();
        std::string object = path;
        object.append("Assets\\Meshes\\Moon_2K.obj");
        std::string texture = path;
        texture.append("Assets\\Textures\\Diffuse_2K.png");
    	
    	for(int i = 0; i < 64; i++)
    	{
            GameObjectID id = Graphite::GameObjectManager::AddGameObject(object, texture);
            m_GameObjects.emplace_back(id);
            glm::vec3 position(32.0f * rand() / RAND_MAX - 16.0f, 32.0f * rand() / RAND_MAX - 16.0f, 32.0f * rand() / RAND_MAX - 16.0f);
            glm::vec3 rotation(32.0f * rand() / RAND_MAX - 16.0f, 32.0f * rand() / RAND_MAX - 16.0f, 32.0f * rand() / RAND_MAX - 16.0f);
            Graphite::GameObjectManager::GetGameObject(id)->GetTransform().Translate(position);
            m_Rotations.emplace_back(rotation);
    	}
    }

	void Tick() override
    {
	    // Code run once per frame in the game loop
        for(int i = 0; i < m_GameObjects.size(); i++)
        {
            Graphite::GameObjectManager::GetGameObject(m_GameObjects[i])->GetTransform().Rotate(m_Rotations[i], glm::radians(0.05f));
        }
    }

	void Shutdown() override
    {
	    // Code run on shutdown of the application
    	
    }

private:
    std::vector<GameObjectID> m_GameObjects;
    std::vector<glm::vec3> m_Rotations;
};

Graphite::Application* Graphite::CreateApp() {
    return new Sandbox();
}
