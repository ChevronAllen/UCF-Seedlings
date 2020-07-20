#pragma once
#include <string>


/**
	@brief A MinigameDescriptor is the object responsible for the data displayed on Screen

	when the minigame is selected.
	This means it will need:
	- Name
	- Description
	- Small Sprite (clickable)
	- Large Sprite (could just be a scaled version of the small sprite, but the larger version also could be more enhanced)
**/
	
class MinigameDescriptor
{
private:
	std::string name,
		description,
		smallSprite,
		largeSprite;

public:
	/**
		@brief Constructor for MinigameDescriptor.
        
		@param n The name of the minigame.
		@param desc The description of the minigame.
		@param smallSpriteLocation Where under source/assets/gfx is the small sprite located.
		@param largeSpriteLocation Where under source/assets/gfx is the large sprite located.
	**/
	MinigameDescriptor(std::string n, std::string desc, std::string smallSpriteLocation, std::string largeSpriteLocation)
	{
		name = n;
		description = desc;
		smallSprite = smallSpriteLocation;
		largeSprite = largeSpriteLocation;
	}

	/**
		@brief Default constructor for MinigameDescriptor allowing for NULL MinigameDescriptor's to be created.
	**/
	MinigameDescriptor() : MinigameDescriptor("NULL", "NULL", "blankMinigameSmall.png", "blankMinigameLarge.png") {}

	///@brief Returns the name of the Minigame
	std::string getName() { return name; };
	///@brief Returns the description of the Minigame
	std::string getDescription() { return description; };
	///@brief Returns the small sprites location of the Minigame
	std::string getSmallSpriteLocation() { return smallSprite; };
	///@brief Returns the large sprites location of the Minigame
	std::string getLargeSpriteLocation() { return largeSprite; };
};