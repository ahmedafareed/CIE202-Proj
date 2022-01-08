#include "Buzzer.h"

Buzzer::Buzzer(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass Buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo, selected); //update to draw Buzzer

}
void Buzzer::setlabel(string label)
{
	m_Label = label;
}
 string Buzzer::getlabel()
{
	 return m_Label;
}

void Buzzer::Operate()
{

}