#include "menu/menuItems/CodeEditorMenuItem.hpp"

#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

#define CELL_HEIGHT 20
#define CELLS_TALL 12

#define LEAST_CELLS_ON_SCREEN 12

CodeEditorMenuItem::CodeEditorMenuItem(int px, int py, int p_borderWidth)
	: CodeEditor(px, py, p_borderWidth), MenuItem()
{
	SetOnRelease([&](int x, int y) { if(GetActive()) InternalSelectCommand(x, y); });
	SetOnDrag([&](int x, int y) { InternalDoDrag(x, y); });
	SetOnDragComplete([&]() { InternalDragComplete(); });
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
CodeEditorMenuItem::~CodeEditorMenuItem()
{

}

bool CodeEditorMenuItem::PointIntersection(int px, int py)
{
	return isPointInside(px, py);
}

void CodeEditorMenuItem::ShiftToTop()
{
	int change = (TOPSCREEN_WIDTH - BOTTOMSCREEN_WIDTH) / 2;
	xShift = change;

	SetActive(false);

	refreshCommandList();
}

void CodeEditorMenuItem::ShiftToBottom()
{
	xShift = 0;

	innerRectangle->setXPosition(x + xShift + borderWidth);
	borderRectangle->setXPosition(x + xShift);
	SetActive(true);

	refreshCommandList();
}

void CodeEditorMenuItem::SelectAbove()
{
	if (GetSelectedCommandIndex() == -1)
		return;

	if(GetSelectedCommandIndex() - 1 != -1)
		SelectCommand(GetSelectedCommandIndex() - 1);
}

void CodeEditorMenuItem::SelectBelow()
{
	if (GetSelectedCommandIndex() == -1)
		return;

	if (GetSelectedCommandIndex() + 1 < commands.size())
	SelectCommand(GetSelectedCommandIndex() + 1);
}