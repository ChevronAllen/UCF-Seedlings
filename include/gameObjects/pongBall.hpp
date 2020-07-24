#pragma once
#include <random>

#include "gameManager.hpp"
#include "resourceManager.hpp"
#include "gameObjects/gameObject.hpp"

class PongBall : public GameObject
{
	/**
		@brief A custom game object used for Pong.
	**/
private:
	SpriteMenuItem *sprite;
	int dirX, dirY, speed; 

			
public:
	/**
	* @brief A custom constructor for setting the ball's velocity, position, angle, and scale.
	*/
	PongBall()
    {
        name = "ball";
		x = TOPSCREEN_WIDTH / 2;
        y = TOPSCREEN_HEIGHT / 2;
        xScale = 1;
        yScale = 1;
        angle = 0;
		speed = 3;

		dirX = rand() % 2 == 0 ? -1 : 1;
		dirY = rand() % 2 == 0 ? -1 : 1;
    }

	/**
	* @brief Delete the balls sprite
	*/
	~PongBall()
	{
		delete(sprite);
	}

	/**
	* @brief Set the ball's sprite's position and scale. 
	*/
    void initialize()
    {
        sprite = new SpriteMenuItem(*(ResourceManager::getSprite("ball.png")));
        sprite->setScale(xScale,yScale);
        sprite->setPosition(x,y);

		//ball needs to be centered on the screen from the center of the ball
		x -= sprite->GetWidth() / 2;
		y -= sprite->GetHeight() / 2;
    }

	/**
	* @brief Calculate and apply ball's velocity.
	*/
    void update() 
	{
		moveTo(speed * dirX, speed * dirY);
    }


	/**
	* @brief Place ball in its original position when a goal is scored.
	*/
	void reset()
	{
		x = TOPSCREEN_WIDTH / 2 - sprite->GetWidth() / 2;
		y = TOPSCREEN_HEIGHT / 2 - sprite->GetHeight() / 2;


		dirX = rand() % 2 == 0 ? -1 : 1;
		dirY = rand() % 2 == 0 ? -1 : 1;
	}

	/**
	* @brief Display the ball to the screen using its sprite.
	*/
    void draw()
    {
        m3d::Screen *screen = GameManager::getScreen();

		sprite->setPosition(x, y);
		screen->drawTop(*sprite, m3d::RenderContext::Mode::Flat, 3);
    }

	/**
	* @brief Returns the top right x position of the ball.
	* @return The top right x position
	*/
	int getXPosition() {
		return sprite->getXPosition();
	}

	/**
	* @brief Returns the top right y position of the ball.
	* @return The top right y position
	*/
	int getYPosition() {
		return sprite->getYPosition();
	}

	/**
	* @brief Returns the center x position of the ball.
	* @return The center x position
	*/
	int getCenterX() {
		return sprite->getCenterX();
	}

	/**
	* @brief Returns the center y position of the ball.
	* @return The y position
	*/
	int getCenterY() {
		return sprite->getCenterY();
	}

	/**
	* @brief Sets the center x and y positions of the ball.
	* @param t_x The x position
	* @param t_y The y position
	*/
	void setCenter(int t_x, int t_y) {
		sprite->setCenter(t_x, t_y);
	}

	/**
	*  @brief Calls the destructor.
	*/
    void destroy(){ this->~PongBall(); }


	/**
	* @brief Adds an offset to the ball's current position.
	* @param _x The x offset
	* @param _y The y offset
	*/
    void moveTo(double _x,double _y)
    {
		y += _y;
		x += _x;
  
    };

	/**
	* @brief Rotates the ball to a given degree (unimplemented).
	* @param deg The degree
	*/
    void Rotate(double deg){};

	/**
	* @brief Switches the ball's x direction.
	*/
	void toggleXDir()
	{
		dirX *= -1;
	}

	/**
	* @brief Switches the ball's y direction.
	*/
	void toggleYDir()
	{
		dirY *= -1;
	}

	/**
	* @brief Sets the ball's x and y directions.
	* @param _directionX The x direction
	* @param _directionY The y direction
	*/
	void SetDirection(int directionX, int directionY)
	{
		if (directionX != 0)
		{
			dirX = directionX;
		}
		if (directionY != 0)
		{
			dirY = directionY;
		}
	}

	/**
	* @brief Returns ball's bounding box.
	* @return The bounding box
	*/
	BoundingBox getAABB()
	{
		return sprite->getBoundingBox();
	}

	/**
	* @brief Returns ball's width.
	* @return The width
	*/
	int getWidth()
	{
		return sprite->GetWidth();
	}

	/**
	* @brief Returns ball's height.
	* @return The height
	*/
	int getHeight()
	{
		return sprite->GetHeight();
	}
};
