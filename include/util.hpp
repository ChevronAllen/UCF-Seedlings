/**
 *  @file util.hpp
 *  @brief Defines the Util class
 */
#pragma once

#include "m3diaLibCI/console.hpp"

#include <m3dia.hpp>

using namespace m3d;

/**
 * @brief sign function
 * 
 * Solution taken from <a href="https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c">stack
 * overflow</a>
 * @returns positive (1), negative (-1), or zero (0) depending on the value of the parameter.
 */
template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

/**
 *  @class Util "util.hpp"
 *  @brief A utility singleton class 
 *  
 *  Util is tasked with providing functions needed by several other classes
*/
class Util
{
	private:
	///Default console in which all Util.Prints will print ot to
	m3dCI::Console* console;
	
	///The active Applet object
	Applet* app;
	///The active screen object
	Screen* scr;
	
	/**
		@brief
		This Class is a singleton. 
		Meaning, only one instance of this class may ever exist.
		This allows for all classes to access this object through the use of this instance value.
		An initial instantiation must occur with proper vaules passed into getInstance
		All further attempts to accesss this class can use dummy values for all parameters of getInstance
	**/
	static Util *instance;
	
	/**
		@brief Constructor for the Util class
		@param screen Screen to draw the console to
		@param applet The current running Game applet
	**/
	Util(Screen* screen, Applet* applet);
	
	public:
	/**
		@brief Deconstructor for Util.
		Responsible for deleting all needed children.
	**/
	~Util();
	
	/**
		@brief The function called each game frame to update all pieces needed by the Util class
	**/
	void OnUpdate();
	
	/**
		@brief Create the initial instance of the Util class
		@param screen Screen to draw the console to
		@param applet The current running Game applet
	**/
	static Util* createInstance(Screen* screen, Applet* applet);
	
	/**
		@brief Get the singleton instance of the Util class
		@returns The singleton instance of the Util class
	**/
	static Util* getInstance();
	
	/**
		@brief Print text to the Console followed by a new line.
		@param text The text to write to the console
	**/
	static void PrintLine(std::string text);
	
	/**
		@brief Print text to the Console.
		@param text The text to write to the console
	**/
	static void Print(std::string text);
	
	/**
		@brief Handles drawing of m3d Objects needed by the Util class
	**/
    void OnDraw();
	
	/**
		@brief Draw a m3d::Drawable object to the Top screen
		@param obj Object to draw
		@param mode RenderContext mode
		@param layer Vertical layer to draw at
	**/
	static void drawTop(Drawable& obj, RenderContext::Mode mode, int layer);
	
	/**
		@brief Draw a m3d::Drawable object to the bottom screen
		@param obj Object to draw
		@param mode RenderContext mode
		@param layer Vertical layer to draw at
	**/
	static void drawBottom(Drawable& obj, RenderContext::Mode mode, int layer);
	
	/**
		@brief Check the Console drawn status
		@returns The drawing status of the Console
	**/
	static bool IsConsoleDrawn();
};