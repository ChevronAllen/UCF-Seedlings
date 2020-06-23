#include "../gameObject.hpp"
#include "../gameManager.hpp"

class PongPaddle : public GameObject
{

	private:
        m3d::Color *color;
        m3d::Rectangle *PongRec;
		int width, height; 
		

	public:
        PongPaddle(int _x, int _y)
        {
            x = _x;
            y = _y;
			width = 10;
			height = 50; 
        }

        ~PongPaddle() {
            color = NULL;
            PongRec = NULL;
        }

        void initialize() {
            color = new m3d::Color(0,0,100);
            PongRec = new m3d::Rectangle(x,y,width,height,*color);
        }

        void update() {
            x = PongRec->getXPosition();
            y = PongRec->getYPosition();
        }

        void draw() {
            m3d::Screen *screen = GameManager::getScreen();
            screen->drawTop(*PongRec);
        }

        void moveTo(double _x, double _y) {
            PongRec->setYPosition(PongRec->getYPosition() + _y);
        }

        void destroy() {
            this->~PongPaddle();
        }

        void Rotate(double deg) {
            PongRec->setPosition(this->y, this->x);
        }

		int getXPosition() {
			return PongRec->getXPosition();
		}

		int getYPosition() {
			return PongRec->getYPosition();
		}

		int getHeight() {
			return PongRec->getHeight();
		}

		int getWidth() {
			return PongRec->getWidth();
		}

		m3d::BoundingBox getBoundingBox() {
			return PongRec->getBoundingBox();
		}
};