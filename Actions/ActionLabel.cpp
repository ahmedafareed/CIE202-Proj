#include "ActionLabel.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"


ActionLabel::ActionLabel(ApplicationManager* pApp) : Action(pApp)
{
}

ActionLabel::~ActionLabel(void)
{
}

void ActionLabel::Execute()
{
	
	
	UI* pUi = pManager->GetUI();
	pUi->PrintMsg(" Click on the component ");
	pUi->GetPointClicked(x, y);
	
	Component* pComp = pManager->componentcheck(x, y);
	Connection* pCon = pManager->connectioncheck(x, y);
	if (pComp == nullptr)
	{
		pUi->PrintMsg("No component located here. Click anywhere to return");
		pUi->GetPointClicked(x, y);
		return;
	}
	else
	{
		pManager->labeledcheck(x, y);
		pUi->ClearStatusBar();
		pUi->PrintMsg("label your component");
		pComp->setlabel(pUi->GetSrting());
		pUi->label(x, y, pComp->getlabel());
		
	}
	if (pCon == nullptr)
	{
		pUi->PrintMsg("No connection located here. Click anywhere to return");
		pUi->GetPointClicked(x, y);
		return;
	}
	else
	{
		pUi->ClearStatusBar();

		pUi->PrintMsg("label your connection");
		pCon->setlabelc(pUi->GetSrting());
		pUi->label(x, y, pCon->getlabelc());
	}

}

void ActionLabel::Undo()
{
}

void ActionLabel::Redo()
{
}
