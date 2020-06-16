#include "../gameObject.hpp"

class PongPaddle : public GameObject
{

	private:

	public:
		virtual void initialize() {};
		virtual void update() = 0;
		virtual void draw() = 0;

		virtual void destroy() = 0;
		virtual void moveTo(double x, double y) = 0;
		virtual void Rotate(double deg) = 0;

		void setAngle(double _angle)
		{
			angle = _angle;
		}
		double getAngle()
		{
			return angle;
		}

		void setScale(double _x, double _y)
		{
			x = _x;
			y = _y;
		}
		m3d::Vector2f getScale()
		{
			m3d::Vector2f scale;
			scale.u = xScale;
			scale.v = yScale;
			return scale;
		}

		void setPosition(double _x, double _y)
		{
			x = _x;
			y = _y;
		}
		m3d::Vector2f getPosition()
		{
			m3d::Vector2f pos;
			pos.u = x;
			pos.v = y;
			return pos;
		}

		bool screenIntersect();


};