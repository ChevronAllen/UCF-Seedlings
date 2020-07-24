#include "scenes/minigame.hpp"


void Minigame::toggleWinCond()
{
	winCond = !winCond;
}

Minigame::Minigame()
{
	m3d::Screen * screen = GameManager::getScreen();
    m_sandbox = new LuaSandbox( [this](){onExecutionBegin();},
                                [this](){onExecutionEnd();});
	
	int margin = 5;

	codeEditor = new CodeEditorMenuItem(margin, (BOTTOMSCREEN_WIDTH * 0.75) - (margin * 2), 1);
	codeEditor->SetActive(false);
	menu->AddItem(codeEditor);

	int buttonWidth = BOTTOMSCREEN_WIDTH * 0.25 - (margin * 2);
	int buttonHeight = (BOTTOMSCREEN_HEIGHT - buttonWidth - (margin * 2)) / 3;

	AddButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	AddButton->SetText("ADD");
	AddButton->SetOnRelease([this](int x, int y) { this->AddButton_OnClick(); });
	AddButton->SetActive(false);

	EditButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	EditButton->SetText("EDIT");
	EditButton->SetOnRelease([this](int x, int y) { this->EditButton_OnClick(); });
	EditButton->SetActive(false);

	RemoveButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 2, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	RemoveButton->SetText("DEL");
	RemoveButton->SetOnRelease([this](int x, int y) { this->DeleteButton_OnClick(); });
	RemoveButton->SetActive(false);

	closeButton = new ButtonMenuItem(48 + BOTTOMSCREEN_WIDTH * 0.5, 0, new m3dCI::Sprite(*ResourceManager::getSprite("tabClose.png")));
	closeButton->SetOnRelease([this](int x, int y) { this->CloseButton_OnClick(); });
	closeButton->SetActive(false);

	submitButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 3, buttonWidth, buttonWidth, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	submitButton->SetText("Run");
	submitButton->SetOnRelease([this](int x, int y) { this->SubmitButton_OnClick(); });
	submitButton->SetActive(false);

	menu->AddItem(submitButton);
	menu->AddItem(closeButton);
	menu->AddItem(EditButton);
	menu->AddItem(RemoveButton);
	menu->AddItem(AddButton);

	commandLister = new CommandListerMenuItem(this);
	commandLister->SetActive(false);
	menu->AddItem(commandLister);

	SetTransitionToDisplayState(DisplayState::CodeEditor);
}

Minigame::~Minigame()
{
	delete(m_sandbox);

	if(commandEditor != nullptr)
		menu->RemoveItem(commandEditor);

	delete(m_gridOverlay);
}

void Minigame::initialize()
{
    m_gridOverlay = new SpriteMenuItem( *ResourceManager::getSprite("minigame_grid.png"));
    m_gridOverlay->setOpacity(50);
}

void Minigame::update()
{
	if (nextState != DisplayState::null)
		FinishTransitionToDisplayState();

    #ifdef DEBUG_MINIGAME
	if (buttons::buttonPressed(buttons::X))
	{
		if(m_sandbox->getThreadState() == THREAD_HALT)
		{
            Util::PrintLine("Thread Running");
			m_sandbox->setThreadState(THREAD_RUNNING);
		}else
        {
            Util::PrintLine("Thread Halted");
            m_sandbox->setThreadState(THREAD_HALT);
        }
	}
	if (buttons::buttonPressed(buttons::Y))
	{
        Util::PrintLine("Thread Queue Clear");
		m_sandbox->setThreadState(THREAD_CLEAR);

	}
    #endif

	if (codeEditor != nullptr)
	{
		AddButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canAdd());
		EditButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canEdit());
		RemoveButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canRemove());
		submitButton->SetActive(isExecuting || blockButtons ? false : true);
	}

	switch (dState)
	{
	case DisplayState::CodeEditor:
		if (codeEditor != nullptr)
		{
			if (Input::btnPressed(m3d::buttons::CPadUp) || Input::btnPressed(m3d::buttons::DPadUp))
				codeEditor->SelectAbove();
			else if (Input::btnPressed(m3d::buttons::CPadDown) || Input::btnPressed(m3d::buttons::DPadDown))
				codeEditor->SelectBelow();
		}
		break;
	case DisplayState::CommandLister:
		if (closeButton != nullptr)
			closeButton->setPosition(48 + BOTTOMSCREEN_WIDTH * 0.5, 0);
		break;
	case DisplayState::CommandEditorCommandLister:
		if (closeButton != nullptr)
			closeButton->setPosition(48 + BOTTOMSCREEN_WIDTH * 0.5, 0);
		break;
	case DisplayState::CommandEditor:
		if (closeButton != nullptr)
			closeButton->setPosition(BOTTOMSCREEN_WIDTH - 37, 0);
		break;
	}

	menu->OnUpdate();
}

void Minigame::draw()
{
	m3d::Screen * scr = GameManager::getScreen();

	Scene::draw();

	if (m_gridOverlay != nullptr && showGridLines)
		GameManager::getScreen()->drawTop(*m_gridOverlay, m3d::RenderContext::Mode::Flat, 1);

	switch (dState)
	{
	case DisplayState::CodeEditor:
		if (codeEditor != nullptr)
			scr->drawBottom(*codeEditor);
		if (AddButton != nullptr)
			scr->drawBottom(*AddButton);
		if (EditButton != nullptr)
			scr->drawBottom(*EditButton);
		if (RemoveButton != nullptr)
			scr->drawBottom(*RemoveButton);
		if (submitButton != nullptr)
			scr->drawBottom(*submitButton);
		break;
	case DisplayState::CommandLister:
		if (AddButton != nullptr)
			scr->drawBottom(*AddButton);
		if (EditButton != nullptr)
			scr->drawBottom(*EditButton);
		if (RemoveButton != nullptr)
			scr->drawBottom(*RemoveButton);
		if (submitButton != nullptr)
			scr->drawBottom(*submitButton);
	case DisplayState::CommandEditorCommandLister:
		if (commandLister != nullptr)
			scr->drawBottom(*commandLister);
		if (closeButton != nullptr)
			scr->drawBottom(*closeButton);
		if (AddButton != nullptr)
			scr->drawBottom(*AddButton);
		if (EditButton != nullptr)
			scr->drawBottom(*EditButton);
		if (RemoveButton != nullptr)
			scr->drawBottom(*RemoveButton);
		if (submitButton != nullptr)
			scr->drawBottom(*submitButton);
		break;
	case DisplayState::CommandEditor:
		if (commandEditor != nullptr)
			scr->drawBottom(*commandEditor);
		if (closeButton != nullptr)
			scr->drawBottom(*closeButton);
		break;
	}
}

void Minigame::SetTransitionToDisplayState(DisplayState state)
{
	if(nextState == DisplayState::null)
		nextState = state;
}

void Minigame::FinishTransitionToDisplayState()
{
	AddButton->SetActive(false);
	RemoveButton->SetActive(false);
	EditButton->SetActive(false);
	closeButton->SetActive(false);

	if (commandEditor != nullptr)
		commandEditor->SetActive(false);
	commandLister->SetActive(false);
	codeEditor->SetActive(false);

	blockButtons = true;

	switch (nextState)
	{
	case DisplayState::CodeEditor:
		codeEditor->SetActive(true);

		AddButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canAdd());
		EditButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canEdit());
		RemoveButton->SetActive(isExecuting || blockButtons ? false : codeEditor->canRemove());
		submitButton->SetActive(isExecuting || blockButtons ? false : true);

		blockButtons = false;
		break;
	case DisplayState::CommandLister:
		//codeEditor->ShiftToTop();

		commandLister->SetActive(true);
		closeButton->SetActive(true);
		break;
	case DisplayState::CommandEditorCommandLister:
		commandLister->SetActive(true);
		closeButton->SetActive(true);
		break;
	case DisplayState::CommandEditor:
		commandEditor->SetActive(true);
		closeButton->SetActive(true);
		break;
	}

	dState = nextState;
	nextState = DisplayState::null;
}

void Minigame::AddButton_OnClick()
{
	SetTransitionToDisplayState(DisplayState::CommandLister);
}

void Minigame::SubmitButton_OnClick()
{
    if(m_sandbox->getThreadState() != THREAD_CLOSE)
    {
        if (submitFunction != nullptr)
        {
            submitFunction(codeEditor->GetCommands());
        }
    }
    #ifdef DEBUG
    else
    {
        Util::PrintLine("warning: thread closed");
    }
    #endif
}

void Minigame::EditButton_OnClick()
{
	if (codeEditor == nullptr || codeEditor->getSelectedObject() == nullptr)
		return;

	if (commandEditor != nullptr)
		menu->RemoveItem(commandEditor);

	commandEditor = new CommandEditorMenuItem(codeEditor->getSelectedObject());
	commandEditor->SetActive(false);
	commandEditor->SetEditFunction
	(
		[&]()
		{
			SetTransitionToDisplayState(DisplayState::CommandEditorCommandLister);
		}
	);

	menu->AddItem(commandEditor);

	SetTransitionToDisplayState(DisplayState::CommandEditor);
}

void Minigame::DeleteButton_OnClick()
{
	codeEditor->removeCommand();
}

void Minigame::CloseButton_OnClick()
{
	m3d::Screen * scr = GameManager::getScreen();

	if (dState == DisplayState::CommandEditor)
		SetTransitionToDisplayState(DisplayState::CodeEditor);
	else if (dState == DisplayState::CommandEditorCommandLister)
		SetTransitionToDisplayState(DisplayState::CommandEditor);
	else if (dState == DisplayState::CommandLister)
		SetTransitionToDisplayState(DisplayState::CodeEditor);
}

void Minigame::AddStartCommands(std::vector<CommandObject*> commands)
{
	for (unsigned int i = 0; i < commands.size(); i++)
		codeEditor->addCommand(commands[i]);
}

void Minigame::AddCommand(CommandObject* command)
{
	m3d::Screen * scr = GameManager::getScreen();

	if (dState == DisplayState::CommandEditorCommandLister)
		codeEditor->replaceCommand(codeEditor->getSelectedObject(), command);
	else if (dState == DisplayState::CommandLister)
		codeEditor->addCommand(command);
	
	if (dState == DisplayState::CommandEditorCommandLister)
		SetTransitionToDisplayState(DisplayState::CommandEditor);
	else
		SetTransitionToDisplayState(DisplayState::CodeEditor);
}

void Minigame::ClearCommands()
{
	codeEditor->ClearCommands();
}

void Minigame::SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction)
{
	submitFunction = callbackFunction;
}

void Minigame::onExecutionBegin()
{
	isExecuting = true;
}

void Minigame::onExecutionEnd()
{
	isExecuting = false;
}