#include "gameManager.hpp" //
#include "sceneManager.hpp" //
#include "scene.hpp"
#include "resources.h" // 
#include "gameObjects/pongPaddle.cpp"

class pongScene : public Scene
{

	private:
		m3d::Rectangle *top, *bottom, *division;
		PongPaddle *leftPaddle, *rightPaddle;
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
			leftPaddle = new PongPaddle(10,70);
			rightPaddle = new PongPaddle(380,70);
			division = new m3d::Rectangle(200,0,5,400,*c2);

			midcourt = new m3d::Circle(150,70,50,*c2);
			midcourtInner = new m3d::Circle(156,75,45,*c1);

			tex = new m3d::Text("Pong", *c2);
			tex->setPosition(160,120);

			leftPaddle->initialize();
			rightPaddle->initialize();
		}

		void draw()
		{
			m3d::Screen *scr = GameManager::getScreen();

			scr->drawTop(*top);
			scr->drawTop(*midcourt);
			scr->drawTop(*midcourtInner);
			scr->drawTop(*division);
			leftPaddle->draw();
			rightPaddle->draw();
			scr->drawBottom(*bottom);
			scr->drawBottom(*tex);
		}

		void load() {};
		void unload() {};
		void update() {
			if (m3d::buttons::buttonDown(m3d::buttons::Button::Up))
			{
				leftPaddle->moveTo(0,-(GameManager::getDeltaTime() + 0.5));
				leftPaddle->update();
			}
			if (m3d::buttons::buttonDown(m3d::buttons::Button::Down))
			{
				 leftPaddle->moveTo(0,1);
			}
			
		};
		void onEnter() {};
		void onExit() {};



};

