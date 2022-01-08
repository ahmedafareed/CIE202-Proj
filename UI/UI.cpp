#include "UI.h"
#include <iostream>
#include "../Components/Component.h"
using namespace std;
UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = BLUE;
	BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Logic Simulator Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}


int UI::getCompWidth() const
{
	return COMP_WIDTH;
}

int UI::getCompHeight() const
{
	return COMP_HEIGHT;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void UI::GetmouseCoord(int& x, int& y)
{
	pWind->GetMouseCoord(x, y);	//Wait for mouse click
}

string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RES:	return ADD_RESISTOR;
			case ITM_GRO:	return ADD_GROUND;
			case ITM_BUZ:	return ADD_BUZZER;
			case ITM_FUS:	return ADD_FUSE;
			case ITM_EXIT:	return EXIT;
			case ITM_CON:	return ADD_CONNECTION;
			case ITM_LABEL:	return LABEL;
			
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
void UI::DrawLine(int x1, int y1, int x2, int y2) const
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(x1, y1, x2, y2);
}

void UI::selectedDrawLine(int x1, int y1, int x2, int y2) const
{
	pWind->SetPen(RED, 2);
	pWind->DrawLine(x1, y1, x2, y2);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
void UI::label(int lblx, int lby,string msg) const
{
	int lbly = lby - getCompHeight();
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(lblx,  lbly, msg);
	 //Print the label

}
void UI::Clearlabel(int lblx, int lby)const
{
	int lbly = lby - getCompHeight();

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(lblx, lbly, getCompWidth(), getCompHeight());
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar() 
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_RES] = "images\\Menu\\Menu_Resistor.jpg";
	MenuItemImages[ITM_GRO] = "images\\Menu\\Menu_Ground1.jpg";
	MenuItemImages[ITM_FUS] = "images\\Menu\\Menu_Fuse1.jpg";
	MenuItemImages[ITM_BUZ] = "images\\Menu\\Menu_Buzzer1.jpg";
	MenuItemImages[ITM_CON] = "images\\Menu\\connection.jpg";
	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menue_Label.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*ToolItemWidth,0,ToolItemWidth, ToolBarHeight);
		pWind->SetPen(RED, 3);
		pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

	//Draw a line under the toolbar
	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawResistor(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	string ResImage;
	if(selected)	
		ResImage ="Images\\Comp\\Resistor_HI.jpg";	//use image of highlighted resistor
	else  
		ResImage = "Images\\Comp\\Resistor.jpg";	//use image of the normal resistor

	//Draw Resistor at Gfx_Info (1st corner)
	pWind->DrawImage(ResImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
	label(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, "resistor");
}

void UI::DrawGround(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string GroImage;
	if (selected)
		GroImage = "Images\\Comp\\Ground_HI.jpg";	//use image of highlighted Ground
	else
		GroImage = "Images\\Comp\\Ground.jpg";	//use image of the normal Ground

	//Draw Ground at Gfx_Info (2ed corner)
	pWind->DrawImage(GroImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
	label(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, "ground");
}
void UI::DrawBuzzer(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string BuzImage;
	if (selected)
		BuzImage = "Images\\Comp\\Buzzer_HI.jpg";	//use image of highlighted Buzzer
	else
		BuzImage = "Images\\Comp\\Buzzer.jpg";	//use image of the normal Buzzer
	
	//Draw buzzer at Gfx_Info (3ed corner)
	pWind->DrawImage(BuzImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
	//pWind->DrawString(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y - getCompHeight(), "buzzer");
	label(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, "Buzzer");
}
void UI::DrawFuse(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string FusImage;
	if (selected)
		FusImage = "Images\\Comp\\Fuse_HI.jpg";	//use image of highlighted Fuse
	else
		FusImage = "Images\\Comp\\Fuse.jpg";	//use image of the normal Fuse

	//Draw fuse at Gfx_Info (4th corner)
	pWind->DrawImage(FusImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
	label(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, "fuze");
}

void UI::DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	if (selected)
	{
		DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);
		
	}
	else
	{
		selectedDrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);
	}
	//label(r_GfxInfo, "connection");
}


//TODO: Add similar functions to draw all other components




//void UI::DrawConnection(const GraphicsInfo &r_GfxInfo1, const GraphicsInfo& r_GfxInfo2, bool selected) const
//{
//	if (selected)
//	{
//		pWind->SetPen(BLACK, 3);
//		pWind->DrawLine(r_GfxInfo1.PointsList->x, r_GfxInfo1.PointsList->y, r_GfxInfo2.PointsList->x, r_GfxInfo2.PointsList->y);
//	}
//	              
//}


UI::~UI()
{
	delete pWind;
}