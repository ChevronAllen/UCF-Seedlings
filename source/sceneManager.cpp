#include "sceneManager.hpp"

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

void  SceneManager::initialize(){}
void  SceneManager::update(){}
void  SceneManager::draw(){}