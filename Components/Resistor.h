#pragma once
#include "Component.h"
#include "Connection.h"
class Resistor:public Component
{
public:
	Resistor(GraphicsInfo *r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the resistor
	virtual void setlabel(string label);
	virtual string getlabel();
};
