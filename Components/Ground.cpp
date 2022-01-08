#include "Ground.h"

Ground::Ground(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawGround(*m_pGfxInfo, selected); //update to draw resistor

}
void Ground::setlabel(string label)
{
	m_Label = label;
}
string Ground::getlabel()
{
	return m_Label;
}
void Ground::Operate()
{

}                    