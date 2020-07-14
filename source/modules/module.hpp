#pragma once

class Module
{

private:

protected:
    bool m_init = false;
    bool m_finished = false;
    virtual void Before();
    virtual void During();

public:
    Module(){}
    virtual ~Module(){};

    bool isFinished(){return m_finished;}

    void onUpdate()
    {
        if(!m_init)
        {
            Before();
            m_init = true;
            return;
        }

        During();
    }
    virtual void onDraw();
};