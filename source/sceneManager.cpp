#include "sceneManager.hpp"
#include "scenes/startScene.cpp"


SceneManager * m_instance = nullptr;


Scene* SceneManager::getScene()
{
    if(m_instance == nullptr)
    {
        return nullptr;
    }

    return m_instance->m_currentScene;
}

void  SceneManager::transitionTo(Scene* t_next)
{
    getInstance();
    m_instance->m_nextScene = t_next;
    //  TODO: asynchronously init and load next scene.

    if(m_instance->m_currentScene != nullptr)
    {
        //  TODO: Unload objects
        //  TODO: Call scene's exit
    }

    //  TODO: swap scenes


}

void  SceneManager::initialize(){
    //  m_currentScene = tester;
    //tester->initialize();
    if(m_instance == NULL)
    {
        m_instance = new SceneManager();
    }
    m_currentScene = new startScene();
}

    void  SceneManager::update()
    {
        m_currentScene->update();
    }

    void  SceneManager::draw()
    {
        m_currentScene->draw();
    }

