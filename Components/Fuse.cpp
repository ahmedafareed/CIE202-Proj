#include "Fuse.h"

Fuse::Fuse(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass fuse drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo, selected); //update to draw fuse

}
void Fuse::setlabel(string label)
{
	m_Label = label;
}
string Fuse::getlabel()
{
	return m_Label;
}

void Fuse::Operate()
{

}