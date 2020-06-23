#include "../gameObject.hpp"
#include "../gameManager.hpp"

class PongPaddle : public GameObject
{

	private:
        m3d::Color *color;
        m3d::Rectangle *PongRec;

	public:
        PongPaddle(int _x, int _y)
        {
            x = _x;
            y = _y;
        }

        ~PongPaddle() {
            color = NULL;
            PongRec = NULL;
        }

        void initialize() {
            color = new m3d::Color(0,0,100);
            PongRec = new m3d::Rectangle(x,y,10,50,*color);
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
};
