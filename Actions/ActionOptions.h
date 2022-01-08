#pragma once

#include "action.h"


class ActionOptions : public Action
{
private:
	int xc, yc, xp, yp;
public:
	ActionOptions(ApplicationManager* pApp);
	virtual ~ActionOptions(void);
//Execute action (code depends on action type)
virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};