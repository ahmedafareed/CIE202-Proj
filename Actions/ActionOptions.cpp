#include "ActionOptions.h"
#include "../UI/UI.h"
#include "../Components/Component.h"
#include "../Components/Resistor.h"
#include "../Components/Fuse.h"
#include "../Components/Ground.h"
#include "..\ApplicationManager.h"
#include "../Components/Buzzer.h"


ActionOptions::ActionOptions(ApplicationManager* pApp) : Action(pApp)
{}

ActionOptions::~ActionOptions(void)
{
}

void ActionOptions::Execute()
{
	

	UI* pUI = pManager->GetUI();
	pUI->GetmouseCoord(xc, yc);
	Component* pComp = pManager->componentcheck(xc, yc);
	

	if (pComp == nullptr)
	{
		pUI->PrintMsg("No component located here. Click anywhere to return(o)");
		pUI->GetPointClicked(xc, yc);
		return;
	}
	else
	{
		
		GraphicsInfo* pGInfoc = new GraphicsInfo(2);
		
		pUI->PrintMsg("if you want to 1-copy press 'c'  2-move press 'm'  3-cut press 'x'");
		string order= pUI->GetSrting();
		pUI->ClearStatusBar();
		pUI->PrintMsg("press where you want to paste");
		pUI->GetmouseCoord(xp, yp);
		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();

		pGInfoc->PointsList[0].x = xp - compWidth / 2;
		pGInfoc->PointsList[0].y = yp - compHeight / 2;
		pGInfoc->PointsList[1].x = xp + compWidth / 2;
		pGInfoc->PointsList[1].y = yp + compHeight / 2;
		
		pManager->AddComponent(pComp);
	if (const Buzzer* ptrC = dynamic_cast<const Buzzer*>(pComp);)
//		{
//			
//			pManager->AddComponent(pBc);
//		}
//		if (typ == "fuze")
//		{
//			Fuse* pFc = new Fuse(pGInfoc);
//			pManager->AddComponent(pFc);
//		}
//		if (typ == "resistor")
//		{
//			Resistor* pRc = new Resistor(pGInfoc);
//			pManager->AddComponent(pRc);
//		}
//		if (typ == "ground")
//		{
//			Ground* pGc = new Ground(pGInfoc);
//			pManager->AddComponent(pGc);
//		}
//		if (order == "x" || order == "m")
//		{
//			delete pComp;
//		}
//
//	}
//
//}

void ActionOptions::Undo()
{
}

void ActionOptions::Redo()
{
}











