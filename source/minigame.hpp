/**
 *  @file minigame.hpp
 *  @brief Defines the minigame inherited class
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>
#include "scene.hpp"
#include <sstream>

#define DEBUG

#define setObjectName(name, id) executeInSandbox("name_table[\"" name "\"] = " + std::to_string(id))

class Minigame : public Scene
{
	private:
        m3d::Thread* m_sandboxThread;
        m3d::Mutex  m_mutex_execution, m_mutex_sandbox, m_mutex_threadState, m_mutex_lua;
        int m_sandboxThreadState = THREAD_RUNNING;
        std::string* m_luaChunk = nullptr;
        //LuaSandbox* m_sandbox = nullptr;

        /**
         * @brief Sandbox thread's main  function.
         * Only called by the minigameclass to initialize the sandboxThread
         * @param param m3d::Parameter, recieves a pointer to the threadState variable
         */
        void sandboxRuntime(m3d::Parameter param)
        {
            m_mutex_sandbox.lock();
            //Util::PrintLine("sandbox: start sandbox thread");
            
            //m_sandbox = new LuaSandbox();
            int* state = param.get<int*>();
            if(state == NULL)
            {
                Util::PrintLine("Error: threadstate not defined, sandbox thread closing.");
                return;
            }
            
            while(true)
            {
                
                //  Lock access to Thread State
                m3d::Lock lock_state(m_mutex_threadState);
                if(*state == THREAD_CLOSE)
                {   //  close Thread
                    break;
                }else if(*state == THREAD_HALT)
                {   
                    continue;
                }                
                lock_state.~Lock();

                
                if(m_luaChunk != nullptr)
                {                    
                    onExecutionBegin();
                    //  TODO: Disable Command Menu
                    std::string t_lua(m_luaChunk->c_str());
                    
                    #ifdef DEBUG
                    Util::PrintLine(t_lua);
                    #endif
                    
                    m3d::Lock lock_sandbox(m_mutex_sandbox);
                    //m_sandbox->executeString(t_lua);
                    m_luaChunk = nullptr;
                    lock_sandbox.~Lock();

                    onExecutionEnd();

                    setThreadState(THREAD_RUNNING);
                }

                m3d::Thread::sleep();
            }
            
        }

        

	protected:
		static bool winCond;
		
        /**
         * @brief Send code to the sandbox thread.
         * @param chunk valid lua code.
         */
        void executeInSandbox(std::string chunk)
        {
            
            //  Wait for any sandbox executions to complete
            m_mutex_execution.lock();
            
            if(m_luaChunk == nullptr)
            {
                m_luaChunk = new std::string(chunk);
            }
            else 
            {
                Util::PrintLine("warning: wait for previous lua code to complete execution");
            }

            //  Allow sandbox thread to continue execution
            m_mutex_sandbox.unlock();
            
        }

        /**
         *  @brief Set the state of the sandbox thread.
         *  Sets the state within both the native and lua environment
         *  @param state state to set
         */
        void setThreadState(int state)
        {
            //  Wait for thread state access
            m3d::Lock lock_state(m_mutex_threadState);
            m_sandboxThreadState = state;
            lock_state.~Lock();

            //m_sandbox->executeString("_EXEC_STATE = " + std::to_string(state));
        }

        /**
         *  @brief Get the state of the sandbox thread
         */
        int getThreadState()
        {
            m3d::Lock lock_state(m_mutex_threadState);
            return m_sandboxThreadState;
        }

        /**
         *  @brief Function called before a sandbox execution
         *  onExecutionBegin is called right before the sandbox executes a chunk
         */
        virtual void onExecutionBegin()
        {
            
        }

        /**
         *  @brief Function called before a sandbox execution
         *  onExecutionEnd is called right after the sandbox executes a chunk.
         */
        virtual void onExecutionEnd()
        {
            
        }

	public:

		virtual bool checkWinCond() = 0;

		void toggleWinCond()
		{
			winCond = !winCond; 
		}

        /**
         *  @brief Default Constructor, should be inherited by child class constructors
         */
        Minigame()
        {                       
            m_sandboxThread = new m3d::Thread( [this](m3d::Parameter p){sandboxRuntime(p);} , &m_sandboxThreadState);
            
            #ifdef DEBUG
            std::stringstream t_debug;
            t_debug << "new sandbox thread: " << m_sandboxThread ;
            Util::PrintLine(t_debug.str() ) ;
            #endif

            m_sandboxThread->start();
        }

        /**
         *  @brief Default Destructor, should be inherited by child class destructor
         */
        ~Minigame()
        {
            m3d::Lock lock(m_mutex_threadState);
            m_sandboxThreadState = THREAD_CLOSE;
            m_sandboxThread->join();
        }

		virtual void loadScene() = 0;
		virtual void loadWinScr() = 0;
		virtual void loadLoseScr() = 0;
		virtual void requestUI() = 0;
		virtual void closeGame() = 0;
	
		virtual void initialize() = 0;
		virtual void load()=0;
		virtual void unload()=0;
		virtual void update()=0;
		virtual void draw()=0;

		virtual void onEnter()=0;
		virtual void onExit()=0;
};





