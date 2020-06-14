#include "gameManager.hpp"
#include "sceneManager.hpp"
#include "scene.hpp"
#include "resources.h"


//using namespace m3d;

class nextScene : public Scene
{

	private:
		m3d::Rectangle *rect1, *rect2;
		m3d::Text* tex;
		m3d::Color *c1, *c2;

	public:
		nextScene()
		{

		}
		void initialize()
		{
			c1 = new m3d::Color(0,0,0);
			c2 = new m3d::Color(150, 150, 150);

			rect1 = new m3d::Rectangle(0,0,400,240, *c2);
			rect2 = new m3d::Rectangle(0, 0, 320, 240, *c2);

			tex = new m3d::Text("Next scene", *c1);
			tex->setPosition(160,120);
		}

		void draw()
		{
			m3d::Screen* scr = GameManager::getScreen();

			scr->drawTop(*rect1);
			scr->drawBottom(*rect2);
			scr->drawBottom(*tex);
		}

		void load() {};
		void unload() {};
		void update() {};
		void onEnter() {};
		void onExit() {};



};

