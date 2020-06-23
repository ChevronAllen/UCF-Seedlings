#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <memory>
#include "gameObject.hpp"

class Scene : public Updateable
{

protected:
    std::map<unsigned int, GameObject*> m_hashmap;
    unsigned int m_idCounter;

public:

    Scene()
    {
        m_hashmap.empty();
        m_idCounter = 0;
    }

    ~Scene()
    {
        auto it =  m_hashmap.cbegin();
        for(;it != m_hashmap.cend(); it++)
        {
            it->second->destroy();
        }
    }

    virtual void initialize()=0;
    virtual void load()=0;
    virtual void unload()=0;
    virtual void update()=0;
    virtual void draw()=0;

    virtual void onEnter()=0;

    virtual void onExit()=0;

    unsigned int addObject(GameObject* obj)
    {
        m_hashmap[m_idCounter] = obj;
        return ++m_idCounter;
    }

    void removeObject(unsigned int t_id)
    {
        m_hashmap[t_id] = NULL;
    }


};
