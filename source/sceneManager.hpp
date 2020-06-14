#pragma once
#include "scene.hpp"

class SceneManager
{
private:

    Scene* m_nextScene;
    static Scene* m_currentScene;

    static SceneManager * m_instance;
    static Scene* getInstance();

public:

    static Scene* getScene();
    static void transitionTo(Scene*);

    static void initialize(Scene*);
    static void update();
    static void draw();


};
