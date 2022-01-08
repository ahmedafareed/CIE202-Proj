#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBuz.h"
#include "Actions\ActionAddFus.h"
#include "Actions\ActionAddGro.h"
#include "Actions\ActionConct.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionLabel.h"



ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	ConCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = nullptr;

	for (int i = 0; i < MaxConCount; i++)
		ConList[i] = nullptr;

	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}

void ApplicationManager::AddConnection(Connection* pCon)
{
	ConList[ConCount++] = pCon;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = nullptr;
	switch (ActType)
	{
		case ADD_RESISTOR:
			pAct= new ActionAddRes(this);
			break;
		case ADD_GROUND:
			pAct = new ActionAddGro(this);
			break;
		case ADD_FUSE:
			pAct = new ActionAddFus(this);
			break;
		case ADD_BUZZER:
			pAct = new ActionAddBuz(this);
			break;
		case ADD_CONNECTION:
			pAct = new ActionConct(this);
			break;
		case LABEL:
			pAct = new ActionLabel(this);
			break;
		case SELECT:
			pAct = new ActionSelect(this);
			break;
		//case OPTIONS:
		//	pAct = new ActionOptions(this);
		//	break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = nullptr;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(pUI);

		for (int i = 0; i < ConCount; i++)
			ConList[i]->Draw(pUI);

}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete pUI;
	
}
Component* ApplicationManager::componentcheck(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		int x1 = CompList[i]->getGraphicsInfo()->PointsList[0].x;
		int y1 = CompList[i]->getGraphicsInfo()->PointsList[0].y;
		int x2 = CompList[i]->getGraphicsInfo()->PointsList[1].x;
		int y2 = CompList[i]->getGraphicsInfo()->PointsList[1].y;
		if (x >= x1 && y >= y1 && 
			x <= x2 && y <= y2)
		{
			return CompList[i];
		}
	}
	return nullptr;
}


Connection* ApplicationManager::connectioncheck(int x, int y)
{
	for (int i = 0; i < ConCount; i++)
	{
		int x1 = ConList[i]->getConctsInfo()->PointsList[0].x;
		int y1 = ConList[i]->getConctsInfo()->PointsList[0].y;
		int x2 = ConList[i]->getConctsInfo()->PointsList[1].x;
		int y2 = ConList[i]->getConctsInfo()->PointsList[1].y;
		if (x >= x1 && y >= y1 &&
			x <= x2 && y <= y2)
		{
			return ConList[i];
		}
	}
	return nullptr;
}
void ApplicationManager::labeledcheck(int x,int y)
{
	for (int i = 0; i < 200; i++)
	{
		int x1 = labeledcomponent[i]->getGraphicsInfo()->PointsList[0].x;
		int y1 = labeledcomponent[i]->getGraphicsInfo()->PointsList[0].y;
		int x2 = labeledcomponent[i]->getGraphicsInfo()->PointsList[1].x;
		int y2 = labeledcomponent[i]->getGraphicsInfo()->PointsList[1].y;
		if (x >= x1 && y >= y1 &&
			x <= x2 && y <= y2)
		{
			pUI->Clearlabel(x, y);

		}
		else
		{
			labeledcomponent[labeledcount++] = componentcheck(x,y);
		}
	}
}