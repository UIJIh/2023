#ifndef _TURN_MANAGER_
#define _TURN_MANAGER_

#include "CSphere.h"
#include <array>
#include <vector>

using std::vector;
using std::array;

class TurnManager
{
private:
	vector<int> playerIdList; 
	int nowTurnPlayerIndex; 
	void resetTurn(); 
	void finishTurn(); 
	bool isMyBallIn;
	
public:
	TurnManager() = delete; 
	TurnManager(const vector<int>& playerIdList); 
	bool turnProcess(const array<CSphere*, 16>& fieldBalls); 
	bool turnFinished(const array<CSphere*, 16>& fieldBalls); 
	void setPlayerBallNum();
	void processTriggerOff();
	void processTriggerOn();
};
#endif