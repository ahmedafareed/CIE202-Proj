#include "ActionSelect.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include <iostream>

ActionSelect::ActionSelect(ApplicationManager* pApp) : Action(pApp)
{
}

ActionSelect::~ActionSelect(void)
{
}

void ActionSelect::Execute()
{

	
	UI* pUi = pManager->GetUI();
	pUi->GetmouseCoord(x, y);
	Component* pComp = pManager->componentcheck(x, y);
	Connection* pCon = pManager->connectioncheck(x, y);

	if (pComp == nullptr)
	{
		//pUi->PrintMsg("No component located here. Click anywhere to return");
		pUi->GetPointClicked(x, y);
	}
	else
	{
		pComp->setSelected(!(pComp->getSelected()));
	}
	if (pCon == nullptr)
	{
		//pUi->PrintMsg("No component located here. Click anywhere to return");
		pUi->GetPointClicked(x, y);
	}
	else
	{
		pCon->setSelected(!(pCon->getSelected()));
	
	}

}

void ActionSelect::Undo()
{
}

void ActionSelect::Redo()
{
}
