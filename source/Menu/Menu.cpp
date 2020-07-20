#include "Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
	for (unsigned int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i] == nullptr)
			continue;

		delete(menuItems[i]);
	}
}

void Menu::OnUpdate()
{
	int touchedThisFrame = Input::btnPressed(m3d::buttons::Touch),
		touchHeldThisFrame = (!touchedThisFrame) && Input::btn(m3d::buttons::Touch),
		touchReleasedThisFrame = Input::btnReleased(m3d::buttons::Touch),
		touchx = m3d::touch::getXPosition(),
		touchy = m3d::touch::getYPosition();

	std::vector<MenuItem*> menuItemsClone(menuItems);

	for (unsigned int i = 0; i < menuItemsClone.size(); i++)
	{
		MenuItem* currentItem = menuItemsClone[i];

		if (currentItem == nullptr || !currentItem->GetActive())
			continue;

		//Check for touch event on Button
		if (touchedThisFrame && currentItem->PointIntersection(touchx, touchy))
			currentItem->CallOnTouch(touchx, touchy);
		else if (touchReleasedThisFrame && currentItem->PointIntersection(lastFrameTouchX, lastFrameTouchY))
		{
			//If an object has the click release, OnHeldLeave should also be called.
			currentItem->CallOnHeldLeave(touchx, touchy);
			currentItem->CallOnRelease(lastFrameTouchX, lastFrameTouchY);
		}
		else if (touchHeldThisFrame && currentItem->PointIntersection(touchx, touchy) && !currentItem->PointIntersection(lastFrameTouchX, lastFrameTouchY))
			currentItem->CallOnHeldEnter(touchx, touchy);
		else if (touchHeldThisFrame && currentItem->PointIntersection(touchx, touchy) && currentItem->PointIntersection(lastFrameTouchX, lastFrameTouchY))
			currentItem->CallOnHeld(touchx, touchy);
		else if (touchHeldThisFrame && currentItem->PointIntersection(lastFrameTouchX, lastFrameTouchY) && !currentItem->PointIntersection(touchx, touchy))
			currentItem->CallOnHeldLeave(touchx, touchy);

		if (draggedLastFrame && touchReleasedThisFrame)
			currentItem->CallOnDragComplete();

		if (Input::isTouchDragging() && Input::getTouchDragOrigin() != nullptr)
		{
			int tX = Input::getTouchDragOrigin()->u;
			int tY = Input::getTouchDragOrigin()->v;

			if (currentItem->PointIntersection(tX, tY))
			{
				currentItem->CallOnDrag(Input::getTouchDragVector().u, Input::getTouchDragVector().v);
			}
		}
	}

	lastFrameTouchX = touchx;
	lastFrameTouchY = touchy;

	draggedLastFrame = Input::isTouchDragging();
}

MenuItem* Menu::AddItem(MenuItem* item)
{
	if(item != nullptr)
		menuItems.push_back(item);

	return item;
}

bool Menu::ContainsItem(MenuItem* item)
{
	for (unsigned int i = 0; i < menuItems.size(); i++)
		if (menuItems[i] == item)
			return true;

	return false;
}

void Menu::RemoveItem(MenuItem* item)
{
	if (item != nullptr)
		menuItems.erase(std::remove(menuItems.begin(), menuItems.end(), item), menuItems.end());
}