#include "gameManager.hpp" //
#include "sceneManager.hpp" //
#include "scene.hpp"
#include "resources.h" // 

class pongScene : public Scene
{

	private:
		m3d::Rectangle *top, *bottom, *leftPaddle, *rightPaddle, *division;
		m3d::Circle *midcourt, *midcourtInner;
		m3d::Text *tex;
		m3d::Color *c1, *c2;

	public:
		pongScene()
		{

		}
		void initialize()
		{
			c1 = new m3d::Color(0,100,0); 
			c2 = new m3d::Color(100,0,0);

			top = new m3d::Rectangle(0,0,400,240, *c1);
			bottom = new m3d::Rectangle(0, 0, 320, 240, *c1);
			leftPaddle = new m3d::Rectangle(10,70,10,50,*c2);
			rightPaddle = new m3d::Rectangle(380,70,10,50,*c2);
			division = new m3d::Rectangle(200,0,5,400,*c2);

			midcourt = new m3d::Circle(150,70,50,*c2);
			midcourtInner = new m3d::Circle(156,75,45,*c1);


			tex = new m3d::Text("Pong", *c2);
			tex->setPosition(160,120);
		}

		void draw()
		{
			m3d::Screen *scr = GameManager::getScreen();

			scr->drawTop(*top);
			scr->drawTop(*leftPaddle);
			scr->drawTop(*rightPaddle);
			scr->drawTop(*midcourt);
			scr->drawTop(*midcourtInner);
			scr->drawTop(*division);
			scr->drawBottom(*bottom);
			scr->drawBottom(*tex);
		}

		void load() {};
		void unload() {};
		void update() {};
		void onEnter() {};
		void onExit() {};



};

