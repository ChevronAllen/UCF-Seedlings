#pragma once
#include <functional>

/**
	@brief A MenuItem is used to holding all actions involved with a object.
	Best used in unison with a m3d::Drawable object
**/
class MenuItem
{
protected:
	int layer;
	bool isActive = true;
	std::function<void(int, int)> OnHeldEnter = nullptr, OnHeld = nullptr, OnHeldLeave = nullptr, OnTouch = nullptr, OnRelease = nullptr, OnDrag = nullptr;
	std::function<void()> OnDragComplete = nullptr;
	
public:
	/**
		@brief Creates a MenuItem
		@param player Vertical layer of an object. Not yet implemented.
	**/
	MenuItem(int player = 0)
	{
		layer = player;
	}

	/**
		@brief Deonstructor for MenuItem.
		Responsible for deleting all needed children.
	**/
	virtual ~MenuItem() { }

	/**
		@brief Sets the OnHeld function.
		@param onHeld Function to call when MenuItem is held
	**/
	void SetOnHeld(std::function<void(int, int)> onHeld) { OnHeld = onHeld; };
	
	/**
		@brief Sets the OnHeldEnter function.
		@param onHeldEnter Function to call when MenuItem is first held
	**/
	void SetOnHeldEnter(std::function<void(int, int)> onHeldEnter) { OnHeldEnter = onHeldEnter; };
	
	/**
		@brief Sets the OnHeldLeave function.
		@param onHeldLeave Function to call when MenuItem is no longer being held
	**/
	void SetOnHeldLeave(std::function<void(int, int)> onHeldLeave) { OnHeldLeave = onHeldLeave; };
	
	/**
		@brief Sets the OnTouch function.
		@param onTouch Function to call when MenuItem is first touched
	**/
	void SetOnTouch(std::function<void(int, int)> onTouch) { OnTouch = onTouch; };
	
	/**
		@brief Sets the OnRelease function.
		@param onRelease Function to call when MenuItem is released over
	**/
	void SetOnRelease(std::function<void(int, int)> onRelease) { OnRelease = onRelease; };
	
	/**
		@brief Sets the OnDrag function.
		@param onDrag Function to call when MenuItem is being dragged over
	**/
	void SetOnDrag(std::function<void(int, int)> onDrag) { OnDrag = onDrag; };
	
	/**
		@brief Sets the OnDragComplete function.
		@param onDragComplete Function to call when a drag finishes over the MenuItem
	**/
	void SetOnDragComplete(std::function<void()> onDragComplete) { OnDragComplete = onDragComplete; };

	/**
		@brief Calls the OnHeld function.
		@param x X coordinate being held this frame
		@param y Y coordinate being held this frame
	**/
	void CallOnHeld(int x, int y) { if(OnHeld != nullptr) OnHeld(x, y); }
	
	/**
		@brief Calls the OnHeldEnter function.
		@param x X coordinate being held this frame
		@param y Y coordinate being held this frame
	**/
	void CallOnHeldEnter(int x, int y) { if (OnHeldEnter != nullptr) OnHeldEnter(x, y); }
	
	/**
		@brief Calls the OnHeldLeave function.
		@param x X coordinate being held this frame last frame
		@param y Y coordinate being held this frame last frame
	**/
	void CallOnHeldLeave(int x, int y) { if (OnHeldLeave != nullptr) OnHeldLeave(x, y); }
	
	/**
		@brief Calls the OnTouch function.
		@param x X coordinate being touched this frame
		@param y Y coordinate being touched this frame
	**/
	void CallOnTouch(int x, int y) { if (OnTouch != nullptr)  OnTouch(x, y); }
	
	/**
		@brief Calls the OnRelease function.
		@param x X coordinate being released this frame
		@param y Y coordinate being released this frame
	**/
	void CallOnRelease(int x, int y) { if (OnRelease != nullptr) OnRelease(x, y); }
	
	/**
		@brief Calls the OnDrag function.
		@param x X coordinate being dragged over this frame
		@param y Y coordinate being dragged over this frame
	**/
	void CallOnDrag(int x, int y) { if (OnDrag != nullptr) OnDrag(x, y); }
	
	/**
		@brief Calls the OnDragComplete function.
		@param x X coordinate being dragged over last frame
		@param y Y coordinate being dragged over last frame
	**/
	void CallOnDragComplete() { if (OnDragComplete != nullptr) OnDragComplete(); }

	/**
		@brief Sets the active state of this MenuItem
		Inactive objects will not be included for possible interactions
		@param state
	**/
	virtual void SetActive(bool state) { isActive = state; }
	
	/**
		@brief Get the Active state of this object
		@returns Active state
	**/
	bool GetActive() { return isActive; }

	/**
		@brief Function responsible for determining Intersection between the object and a specific XY Coordinate
		Each deriving Object needs to assign this
	**/
	virtual bool PointIntersection(int x, int y) { return false; };
};