#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "gameManager.hpp"
#include "sceneManager.hpp"
#include "resourceManager.hpp"
#include "gameObjects/gameObject.hpp"
#include "gameObjects/pongBall.hpp"


#define PADDLE_EPSILON 10
#define PADDLE_STRAY 5

class PongPaddle : public GameObject
{
	/**
		@brief A custom game object used for Pong.
	**/
private:
    m3d::Rectangle *PongRec;
	int velo; 

	int chanceToFail = 0;
	bool purposelyFail = false;

	int width, height;
	int startX, startY;

	int ballid;

public:
	/**
	* @brief A custom constructor for setting the player paddle's position, scale, angle, and velocity.
	*/
	PongPaddle(int _x, int _y)
	{
		x = _x;
		y = _y;
		startX = _x;
		startY = _y;
		xScale = 1;
		yScale = 1;
	}

	/**
	* @brief A custom constructor for setting the enemy paddle's velocity, position, angle, scale and ball.
	* 
	*/
	PongPaddle(int _x, int _y, int ballID)
	{
		x = _x;
		y = _y;
		startX = _x;
		startY = _y;
		xScale = 1;
		yScale = 1;

		ballid = ballID;
	}

	/**
	* @brief Delete the Paddles rectangle
	*/
	~PongPaddle()
	{
		delete(PongRec);
	}
	
	/**
	* @brief Set the paddle's sprite's position and scale.
	*/
    void initialize() {
		width = 10;
		height = 45;

		angle = 0;
		velo = 3;

		m_color = m3d::Color(255, 255, 255);

		PongRec = new Rectangle((int)x, (int)y, width, height, m_color);
    }

	/**
	* @brief Determine the paddle's velocity.
	*/
    void update() 
	{
		if(ballid == -1)
			return;

		PongBall* ball = static_cast<PongBall*>(SceneManager::getScene()->findObject(ballid));
		if (ball != nullptr)
		{
            //target_x = ball->getPosition().u;

			// calculate displacement between enemy paddle and ball 
            int yCenter = (y + (PongRec->getHeight() / 2));
            int ballCenter = (ball->getYPosition() + (ball->getHeight() / 2));            
            target_y = ballCenter + (PADDLE_STRAY * (chanceToFail/4.0));
			
            int diff = yCenter - target_y;


			// enemy paddle moves towards the ball based on its displacement
			// if (diff > 0)
			// 	moveTo(0, purposelyFail ? velo: -velo);
			// else if (diff < 0)
			// 	moveTo(0, purposelyFail ? -velo : velo);

            if(abs(diff) > PADDLE_EPSILON)
            {
                moveTo(0, -sign(diff) * velo) ;
            }
            //sign(diff) * min( 1.0,  ( abs(yCenter - target_y) / (PADDLE_EPSILON*2) ) )
		}
    }

	/**
	* @brief Calculate the enemy paddle's chance to fail each time the the ball hits its paddle.
	*/
	void ballBouncedOffPaddle()
	{
		chanceToFail += 10;

		int random = rand() % 100;

		purposelyFail = random < chanceToFail;
	}

	/**
	* @brief Display the paddle to the screen using its sprite.
	*/
    void draw() {
        m3d::Screen *screen = GameManager::getScreen();

		PongRec->setPosition(x, y);
		PongRec->setWidth(xScale * width);
		PongRec->setHeight(yScale * height);
		PongRec->setColor(m_color);

		screen->drawTop(*PongRec, m3d::RenderContext::Mode::Flat, 3);
    }

	/**
	* @brief Adds an offset to the paddle's current position and
	* prevents the paddle from going out of bounds.
	* @param _x The x offset
	* @param _y The y offset
	*/
    void moveTo(double _x, double _y) {
		y += _y;
		x += _x;
		
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		if (x > TOPSCREEN_WIDTH)
			x = TOPSCREEN_WIDTH;
		if (y + PongRec->getHeight() > TOPSCREEN_HEIGHT)
			y = TOPSCREEN_HEIGHT - PongRec->getHeight();
    }

	/**
	* @brief Returns the top left x position of the paddle.
	* @return The top right x position
	*/
	int getXPosition() {
		return x;
	}

	/**
	* @brief Returns the top left y position of the paddle.
	* @return The top right y position
	*/
	int getYPosition() {
		return y;
	}

	/**
	* @brief Returns the center x position of the paddle.
	* @return The center x position
	*/
	int getCenterX() {
		return PongRec->getXPosition() + PongRec->getWidth() / 2;
	}

	/**
	* @brief Returns the center y position of the paddle.
	* @return The y position
	*/
	int getCenterY() {
		return PongRec->getYPosition() + PongRec->getHeight() / 2;
	}

	/**
	* @brief Sets the center x and y positions of the paddle.
	* @param t_x The x position
	* @param t_y The y position
	*/
	void setCenter(int t_x, int t_y) {
		//PongRec->setCenter(t_x, t_y);
	}


	/**
	* @brief Place the paddle in its original position when a goal is scored and
	* and reset the enemy paddle's chance to fail. 
	*/
	void reset(bool resetScale = false)
	{
		x = startX;
		y = startY;

		if (resetScale)
		{
			xScale = 1;
			yScale = 1;
		}

		m_color = m3d::Color(255, 255, 255);

		chanceToFail = 0;
		purposelyFail = false;
	}

	/**
	*  @brief Calls the destructor.
	*/
	void destroy() 
	{ 
		delete(PongRec);
		//this->~PongPaddle(); 
	}

	/**
	* @brief Rotates the paddle to a given degree (unimplemented).
	* @param deg The degree
	*/
	void Rotate(double deg) {};

	/**
	* @brief Returns paddle's bounding box.
	* @return The bounding box
	*/
	BoundingBox getAABB()
	{
		return PongRec->getBoundingBox();
	}

	/**
		@brief Overrides the GameObject SetPosition function. 
		Keeps the paddle within screen bounds.
	*/
	void setPosition(double t_x, double t_y)
	{
		if (t_x < 0)
			t_x = 0;
		if (t_y < 0)
			t_y = 0;
		if (t_x > TOPSCREEN_WIDTH)
			t_x = TOPSCREEN_WIDTH;
		if (t_y + PongRec->getHeight() > TOPSCREEN_HEIGHT)
			t_y = TOPSCREEN_HEIGHT - PongRec->getHeight();

		x = t_x;
		y = t_y;
	}

	/**
		@brief Implement the GameObject setScale function.
		@param t_x X Scale
		@param t_y Y Scale
	*/
	void setScale(double t_x, double t_y)
	{
		xScale = t_x;
		yScale = t_y;
	}

	/**
		@brief Implement the GameObject setColor function.
		@param t_color Color to change to
	*/
	void setColor(m3d::Color t_color)
	{
		m_color = t_color;
	}
};
