#pragma once

#include "menu.hpp"

class MinigameTemplateMenu : public Menu
{
	private:
		m3dCI::Button *AddButton = nullptr,
			*RemoveButton = nullptr;
		m3dCI::CodeEditor* codeEditor = nullptr;
		m3dCI::CommandLister* commandLister = nullptr;

		bool showCommandLister = false;
	public:
		MinigameTemplateMenu(m3d::Screen* screen);
		virtual ~MinigameTemplateMenu();

		void AddCommand(std::string command);

		void AddButton_OnClick(m3dCI::Button* button);
		void DeleteButton_OnClick(m3dCI::Button* button);
		
		void OnUpdate();
};