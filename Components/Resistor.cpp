#include "Resistor.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo, selected); //update to draw resistor

}
void Resistor::setlabel(string label)
{
	m_Label = label;
}
string Resistor::getlabel()
{
	return m_Label;
}

void Resistor::Operate()
{

}