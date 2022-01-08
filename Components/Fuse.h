#pragma once
#include "Component.h"

class Fuse :public Component
{
public:
	Fuse(GraphicsInfo* r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the Fuse
	virtual void setlabel(string label);
	virtual string getlabel();

};