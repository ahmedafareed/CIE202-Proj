#ifndef __UI_H_
#define __UI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"
#include <string>
using namespace std;

struct Point
{
	int x,y;
};


//A structure to contain drawing parameters for each component/connection
//Each component stores its drawing points in this struct 
//For example, a resistor can store points of the rectangluar area it occupies
//The Connection can store the points of its line segments
//this structure can be extended if desired
struct GraphicsInfo
{
	int PointsCount;
	Point* PointsList;
	GraphicsInfo(int PtsCnt)
	{
		PointsCount = PtsCnt;
		PointsList = new Point[PointsCount];	//allocate required points
	}

};
struct ConctsInfo
{
	int PointsCount;
	Point* PointsList;
	ConctsInfo(int PtsCnt)
	{
		PointsCount = PtsCnt;
		PointsList = new Point[PointsCount];	//allocate required points
	}

};

class UI
{

	enum DsgnMenuItem //The items of the design menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_RES,		//Resistor item in menu
		ITM_GRO,		//Ground item in menu
		ITM_FUS,		//Fuse item in menu
		ITM_BUZ,		//Buzzer item in menu
		ITM_CON,
		ITM_LABEL,
		ITM_EXIT,		//Exit item
		//TODO: Add more items names here
	
		ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	};


	enum SimMenuItem //The items of the simulation menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in menu
		ITM_CIRC_SIM,	//Circuit Simulate menu item
	
		//TODO:Add more items names here
	
		ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
	};



	MODE AppMode;		//Application Mode (design or simulation)
	
	static const int	width = 1200, height = 650,	//Window width and height
						wx = 15 , wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,	//Status Bar Height
						ToolBarHeight = 80,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
						ToolItemWidth = 80,		//Width of each item in toolbar menu

						//Arbitrary values, you can change as you wish
						COMP_WIDTH = 100,		//Component Image width
						COMP_HEIGHT = 30;		//Component Image height

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color



	window *pWind;
	
public:
	
	UI();
	int getCompWidth() const;	//returns Component width
	int getCompHeight() const;	//returns Component height
	
	
	// Input Functions  ---------------------------
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	void GetmouseCoord(int&, int&);	//Get coordinate where user clicks with no wait
	string GetSrting();		//Returns a string entered by the user

	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	
	// Output Functions  ---------------------------
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void Clearlabel(int lblx, int lby)const;
	void ClearDrawingArea() const;	//Clears the drawing area
	//bool select(const GraphicsInfo& r_GfxInfol);
		
	// Draws a resistor
	void DrawResistor(const GraphicsInfo &r_GfxInfo, bool selected = false) const; // selected was=fales 
	// Draws a Ground
	void DrawGround(const GraphicsInfo &r_GfxInfo, bool selected=false) const;
	// Draws a Buzzer
	void DrawBuzzer(const GraphicsInfo& r_GfxInfo, bool selected = false) const;
	// Draws a Fuse
	void DrawFuse(const GraphicsInfo& r_GfxInfo, bool selected = false) const;

	void DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected) const;

	// Draws Line
	void DrawLine(int x1, int y1, int x2, int y2) const;
	void selectedDrawLine(int x1, int y1, int x2, int y2) const;
	
	void PrintMsg(string msg) const;	//Print a message on Status bar
	void label(int lblx, int lbly, string msg) const;

	~UI();
};

#endif