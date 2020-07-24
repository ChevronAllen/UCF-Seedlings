#include "m3diaLibCI/console.hpp"

namespace m3dCI
{
	//Default Console constructor. Creates a background with a textbox for console output
	Console::Console(std::string defaultText):
		toggleState(false),
		consoleTextBox(defaultText),
		consoleBlackRectangle(0, 0, 1000, 1000, m3d::Color(50,100,200))//console background needs to be as big as the screen size, 1000, 1000 is good enough for both screens
	{
		consoleTextBox.setFontSize(0.5);
		consoleTextBox.setFontWeight(0.5);
	}

	//Deconstructor: Delete objects which were created solely for this object.
	Console::~Console()
	{

	}

	//Toggle the state of the console (visible to invisible)
	void Console::ToggleState()
	{
		toggleState = !toggleState;
	}
	
	//Determine how to draw the Console
	//Must draw both the textbox and the background
	void Console::draw(m3d::RenderContext t_context)
	{
		if(toggleState)
		{
			consoleBlackRectangle.draw(t_context);
			consoleTextBox.draw(t_context);
		}
	}
	
	//Print function
	//Prints the last 10 lines, any previous lines after are ignored
	void Console::print(std::string text)
	{
		std::string combinedText = consoleTextBox.getText() + text;

		int counter = 0;
		std::size_t foundSize;
		std::string substring = combinedText;

		do
		{
			foundSize = substring.find("\n");

			if (foundSize != std::string::npos)
			{
				std::size_t substringSize = substring.size();
				if (foundSize > substringSize)
					break;

				counter++;
				substring = substring.substr(foundSize + 1, substringSize);
			}
		} while (foundSize != std::string::npos);

		if (counter >= 10)
		{
			//only grab the last 10 new lines.
			int index = counter - 9;//from 0 -> 10

			counter = 0;
			substring = combinedText;
			do
			{
				foundSize = substring.find("\n");

				std::size_t substringSize = substring.size();

				if (counter == index)
				{
					combinedText = substring;
					break;
				}

				if (foundSize > substringSize)
				{
					combinedText = substring;
					break;
				}

				counter++;
				substring = substring.substr(foundSize + 1, substringSize);
			} while (foundSize != std::string::npos);
		}
		
		consoleTextBox.setText(combinedText);
	}
	
	//Print function
	//Prints a piece of information with a new line preceding it
	void Console::println(std::string text)
	{
		Console::print("\n" + text);
	}
	
	//Determine if the console is being drawn
	bool Console::isDrawn()
	{
		return toggleState;
	}
}