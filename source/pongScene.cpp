#include "gameManager.hpp" //
#include "sceneManager.hpp" //
#include "scene.hpp"
#include "resources.h" // 

class pongScene : public Scene
{

	private:
		m3d::Rectangle *top, *bottom;
		m3d::Text *tex;
		m3d::Color *c1, *c2;

	public:
		pongScene()
		{

		}
		void initialize()
		{
			c1 = new m3d::Color(0,100,0); 
			c2 = new m3d::Color(150, 150, 150);

			top = new m3d::Rectangle(0,0,400,240, *c1);
			bottom = new m3d::Rectangle(0, 0, 320, 240, *c1);

			tex = new m3d::Text("Pong", *c2);
			tex->setPosition(160,120);
		}

		void draw()
		{
			m3d::Screen *scr = GameManager::getScreen();

			scr->drawTop(*top);
			scr->drawBottom(*bottom);
			scr->drawBottom(*tex);
		}

		void load() {};
		void unload() {};
		void update() {};
		void onEnter() {};
		void onExit() {};



};

