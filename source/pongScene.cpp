#include "gameManager.hpp" 
#include "sceneManager.hpp" 
#include "scene.hpp"
#include "resources.h" 
//#include "gameObjects/pongPaddle.cpp"
#include "gameObjects/pongBall.cpp"
#include <cstdlib>

class pongScene : public Scene
{

	private:
		m3d::Rectangle *top, *bottom, *division;
		PongPaddle *leftPaddle, *rightPaddle;
		PongBall* ball; 
		m3d::Circle *midcourt, *midcourtInner;
		m3d::Text *tex;
		m3d::Color *c1, *c2;
		int dirX, dirY, startX, startY;

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
			ball = new PongBall(150, 70);

			midcourt = new m3d::Circle(150,70,50,*c2);
			midcourtInner = new m3d::Circle(156,75,45,*c1);

			tex = new m3d::Text("Pong", *c2);
			tex->setPosition(160,120);

			leftPaddle->initialize();
			rightPaddle->initialize();
			ball->initialize();
			
			startX = ball->getXPosition();
			startY = ball->getYPosition();
			dirX = -1; 
			dirY = 0;
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
			ball->draw();
			
			scr->drawBottom(*bottom);
			scr->drawBottom(*tex);
		}

		void load() {};
		void unload() {};

		// TODO: 
		//  - calculate the reflection angle
		// - make a normalize function for vectors
		// - make the ball move continously on start
		// - set texture for pong scene

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

			ball->setVelocity(dirX, dirY);
			ball->update();

			if (ball->getXPosition() > 400 || 0 > ball->getXPosition())
			{
				ball->~PongBall();
				ball = new PongBall(150, 70);
				ball->initialize();

				dirX = -1;
				dirY = 0;
			}
			
		
			if (ball->getXPosition() - 1 <= leftPaddle->getXPosition())
			{
				//ball->moveTo(0 - (leftPaddle->getWidth() / 2) - 1 , ball->getYPosition());
				//dirX *= -1;
			}

			/*
			if (ball->getBoundingBox().intersects(leftPaddle->getBoundingBox())) 
			{
				
				int hitpoint = (ball->getYPosition() - leftPaddle->getYPosition()) / leftPaddle->getHeight();

				if (hitpoint > 0)
				{
					dirY = -1;
				}
				else if (hitpoint < 0)
				{
					dirY = 1;
				}

				dirX *= -1;
			}
			*/
	
			
			

	

			
			
			
			
		};
		void onEnter() {};
		void onExit() {};



};

