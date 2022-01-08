#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 , MaxConCount = (MaxCompCount) * (MaxCompCount - 1) / 2};	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	int ConCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Connection* ConList[MaxConCount];
	Component* labeledcomponent[MaxCompCount];
	UI* pUI; //pointer to the UI
	int labeledcount;

public:


public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	void AddConnection(Connection* pCon);

	//destructor
	~ApplicationManager();
	Component* componentcheck(int x, int y);
	
	Connection* connectioncheck(int x, int y);
	void labeledcheck(int x, int y);
};


//this is 
#endif