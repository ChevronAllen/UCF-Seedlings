#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "pongPaddle.cpp"
#include <math.h>


class PongBall : public GameObject
{

	private:
        m3d::Color *color;
        m3d::Circle *PongCir;
		int radius;
		m3d::Vector2f velo; 

	public:
        PongBall(int _x, int _y)
        {
            x = _x;
            y = _y;
			radius = 5;
        }

        ~PongBall() {
            color = NULL;
            PongCir = NULL;
        }

        void initialize() {
            color = new m3d::Color(0,100,100);
            PongCir = new m3d::Circle(x,y,radius,*color);
        }

        void update() {
			PongCir->setXPosition(PongCir->getXPosition() + velo.u);
			PongCir->setYPosition(PongCir->getYPosition() + velo.v);

			x = PongCir->getXPosition();
			y = PongCir->getYPosition();
        }

        void draw() {
            m3d::Screen *screen = GameManager::getScreen();
            screen->drawTop(*PongCir);
        }

		
        void moveTo(double _x, double _y) {
			PongCir->setXPosition(_x);
			PongCir->setYPosition(_y);
			//x = _x;
			//y = _y;
        }

		

        void destroy() {
            this->~PongBall();
        }

        void Rotate(double deg) {
            PongCir->setPosition(this->y, this->x);
        }
		
		int getXPosition() {
			return PongCir->getXPosition();
		}

		int getYPosition() {
			return PongCir->getYPosition();
		}
		

		int getRadius() {
			return PongCir->getRadius();
		}

		m3d::BoundingBox getBoundingBox() {
			return PongCir->getBoundingBox();
		}

		m3d::Vector2f getVelocity() {
			return velo; 
		}

		void setVelocity(int x, int y) {
			velo.u = x;
			velo.v = y;
		}

};