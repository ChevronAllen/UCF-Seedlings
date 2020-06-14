#include "button.hpp"

//Creates a Rectangle to take the form of a button
m3dCI::Button::Button(int px, int py, int pw, int ph, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth = 3)
: m3d::Drawable()
{
	SetDefaults();

	x = px;
	y = py;
	w = pw;
	h = ph;
	innerColor = p_innerColor;
	outerColor = p_borderColor;

	borderWidth = p_borderWidth;
	
	outerRectangle = new m3d::Rectangle(x, y, w, h, outerColor);
	innerRectangle = new m3d::Rectangle(x, y, w, h, innerColor);

	UpdateShape();

	buttonType = Rectangle;
}

//Creates a Sprite from a specific texture to take the form of a button
m3dCI::Button::Button(int px, int py, m3d::Texture& t_texture)
	: m3d::Drawable()
{
	SetDefaults();

	x = px;
	y = py;

	sprite = new m3dCI::Sprite();
	sprite->setTexture(t_texture);

	w = sprite->m_sprite.params.pos.w;
	h = sprite->m_sprite.params.pos.h;

	UpdateShape();

	buttonType = SpriteObject;
}

//Creates a Sprite from a spritesheet to take the form of a button
m3dCI::Button::Button(int px, int py, const std::string& t_spriteSheet, int t_imageId = 0)
	: m3d::Drawable()
{
	SetDefaults();

	x = px;
	y = py;

	sprite = new m3dCI::Sprite(t_spriteSheet, t_imageId);

	w = sprite->m_sprite.params.pos.w;
	h = sprite->m_sprite.params.pos.h;

	UpdateShape();

	buttonType = SpriteObject;
}

//Creates a Circle to take the form of a button
m3dCI::Button::Button(int px, int py, int pr, m3d::Color p_innerColor, m3d::Color p_borderColor, int p_borderWidth = 3)
: m3d::Drawable()
{
	SetDefaults();

	x = px;
	y = py;
	r = pr;
	w = r * 2;
	innerColor = p_innerColor;
	outerColor = p_borderColor;

	borderWidth = p_borderWidth;

	outerCircle = new m3d::Circle(x, y, r, outerColor);
	innerCircle = new m3d::Circle(x, y, r, innerColor);

	UpdateShape();

	buttonType = Circle;
}

//Default Destructor. Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
m3dCI::Button::~Button()
{
	//The following commented out object don't have deletion support. They *should* be grabbed by the garbage collector. 
	//Ideally, we would change these objects to support a default virtual deconstructor
	/*delete(innerRectangle);
	delete(outerRectangle);
	delete(innerCircle);
	delete(outerCircle);*/
	delete(sprite);
	delete(text);
}

//Function used to recreate the shape of the object based off movements/scaling
void m3dCI::Button::UpdateShape()
{
	if (outerRectangle != nullptr)
	{
		outerRectangle->setXPosition(x);
		outerRectangle->setYPosition(y);
		outerRectangle->setWidth(w);
		outerRectangle->setHeight(h);
		outerRectangle->setColor(outerColor);

		innerRectangle->setXPosition(x + borderWidth);
		innerRectangle->setYPosition(y + borderWidth);
		innerRectangle->setWidth(w - (borderWidth * 2));
		innerRectangle->setHeight(h - (borderWidth * 2));
		innerRectangle->setColor(innerColor);
	}
	else if (outerCircle != nullptr)
	{
		outerCircle->setXPosition(x);
		outerCircle->setYPosition(y);
		outerCircle->setRadius(r);

		w = r * 2;
		h = r * 2;

		outerCircle->setColor(outerColor);

		innerCircle->setXPosition(x + (borderWidth * 2));
		innerCircle->setYPosition(y + (borderWidth * 2));
		innerCircle->setRadius(r - (borderWidth * 2));
		innerCircle->setColor(innerColor);
	}
	else if (sprite != nullptr)
	{
		sprite->setPosition(x, y);
	}

	if (text != nullptr)
	{
		int textW = text->getWidth();
		int textH = text->getHeight();

		int centralX = x + (w - textW) / 2;
		int centralY = y + (h - textH) / 2;

		text->setXPosition(centralX);
		text->setYPosition(centralY);
	}
}

//Determines which shape to draw when called via screen.drawTop
void m3dCI::Button::draw(m3d::RenderContext t_context)
{
	if (buttonType == Rectangle)
	{
		if(outerRectangle != nullptr)
			outerRectangle->draw(t_context);
		if (innerRectangle != nullptr)
			innerRectangle->draw(t_context);
	}
	else if (buttonType == Circle)
	{
		if (outerCircle != nullptr)
			outerCircle->draw(t_context);
		if (innerCircle != nullptr)
			innerCircle->draw(t_context);
	}
	else if (buttonType == SpriteObject)
	{
		if (sprite != nullptr)
			sprite->draw(t_context);
	}

	if (text != nullptr)
		text->draw(t_context);
}

//Set the default values for any Button to null, then override them as seen fit
void m3dCI::Button::SetDefaults()
{
	innerRectangle = nullptr;
	innerCircle = nullptr;
	outerRectangle = nullptr;
	outerCircle = nullptr;

	sprite = nullptr;

	text = nullptr;

	OnTouch = nullptr;
	OnHeld = nullptr;
	OnRelease = nullptr;
}

//Determine if a point intersects the Button
bool m3dCI::Button::PointIntersects(int p_x, int p_y)
{
	if(buttonType == Rectangle || buttonType == SpriteObject)
		return getBoundingBox().intersects(m3d::BoundingBox(p_x, p_y, 1, 1));
	else if(buttonType == Circle)
	{
		//Circle bounding box is a box based at the center, but does not contain the bottom of the circle.
		//Therefore, a custom implementation was needed.
		
		int xDiff = x + (r) - p_x;
		int yDiff = y + (r) - p_y;
		
		if(pow(xDiff, 2) + pow(yDiff, 2) <= pow(r, 2))
		{
			return true;
		}
	}
		
	return false;
}

void m3dCI::Button::SetText(std::string txt)
{
	if (text == nullptr)
		text = new m3dCI::Text(txt, m3d::Color(0, 0, 0));
	else
		text->setText(txt);

	UpdateShape();
}

void m3dCI::Button::SetTextColor(m3d::Color color)
{
	if (text != nullptr)
		text->setColor(color);
}
			
/*

	The following functions are all child functions of Rectangle/Circle objects which are used here.

*/	
void m3dCI::Button::setXPosition (int t_x)
{
	x = t_x;
	UpdateShape();
}

int m3dCI::Button::getXPosition ()
{
	return x;
}

void m3dCI::Button::setYPosition (int t_y)
{
	y = t_y;
	UpdateShape();
}

int m3dCI::Button::getYPosition ()
{
	return y;
}

void m3dCI::Button::setPosition (int t_x, int t_y)
{
	x = t_x;
	y = t_y;
	UpdateShape();
}

void m3dCI::Button::setRadius (int t_radius)
{
	if (buttonType == Circle)
		r = t_radius;

	UpdateShape();
} 

void m3dCI::Button::setWidth (int t_width)
{
	if (buttonType == Rectangle)
		w = t_width;

	if (buttonType == Circle)
		r = t_width / 2;

	UpdateShape();
}

int m3dCI::Button::getWidth ()
{
	return w;
}

void m3dCI::Button::setHeight (int t_height)
{
	if (buttonType == Rectangle)
		h = t_height;

	if (buttonType == Circle)
		r = t_height / 2;

	UpdateShape();
}

int m3dCI::Button::getHeight ()
{
	return h;
}

int m3dCI::Button::getRadius ()
{
	return r;
}

m3d::BoundingBox m3dCI::Button::getBoundingBox ()
{
	if (buttonType == Rectangle && outerRectangle != nullptr)
		return outerRectangle->getBoundingBox();
	else if (buttonType == Circle && outerCircle != nullptr)
		return outerCircle->getBoundingBox();
	else if (buttonType == SpriteObject && sprite != nullptr)
	{
		int p_w = sprite->m_sprite.params.pos.w;
		int p_h = sprite->m_sprite.params.pos.h;

		return m3d::BoundingBox(x,y, p_w, p_h);
	}
		
	return m3d::BoundingBox(0,0,0,0);
}

void m3dCI::Button::setInnerColor (m3d::Color t_color)
{
	innerColor = t_color;
	UpdateShape();
}

void m3dCI::Button::setBorderColor(m3d::Color t_color)
{
	outerColor = t_color;
	UpdateShape();
}

m3d::Color m3dCI::Button::getInnerColor ()
{
	return innerColor;
}

m3d::Color m3dCI::Button::getBorderColor()
{
	return outerColor;
}