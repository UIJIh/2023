#ifndef _DISPLAYMANAGER_
#define _DISPLAYMANAGER_

#include <vector>
#include <string>
#include <array>

#include "Player.h"
#include "d3dUtility.h"
#include "d3dfont.h"
#include "Status.h"
#include "CHole.h"
#include "CSphere.h"
#include "CHole.h"
#include "FoulManager.h"

using std::vector;
using std::string;

class DisplayManager 
{
private:

	int windowWidth; 
	int windowHeight; 

	string playerName[2]; 
	string playerBallCount[2]; 
	string playerBallType[2]; 

	string turnStatus; 

	Player* players; 
	CD3DFont* FontObjects[7]; 
	
public:
	DisplayManager(const int windowWidth, const int windowHeight, Player* players);
	~DisplayManager();

	bool create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice);
	void destroy();
	bool update(); 

private:
	string _getFirstBallType(const BallType b);
	//string _getHoleBallType();
	string _getTurnStatus();
	string _getFaulStatus ();
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif