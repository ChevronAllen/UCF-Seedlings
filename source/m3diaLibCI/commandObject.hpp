#pragma once
#include "text.hpp"
#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <algorithm>

namespace m3dCI
{
	class CommandObject
	{
	private:
		m3d::Rectangle* backgroundRectangle;
		m3dCI::Text* commandTextObject;

	public:
		CommandObject(int x, int y, int w, int h, std::string command, bool selected);
		~CommandObject();

		void draw(m3d::RenderContext t_context);
		void setBackgroundColor(m3d::Color color);
		void setPosition(int x, int y);
	};
}