#ifndef _FOULMANAGER_
#define _FOULMANAGER_

class FoulManager
{
	void QueBallInHole();
	bool BlackBallInHole();
	bool BlackBallWithFoul(); 

public:
	FoulManager();
	void reset(); 
	void checkFoul(); 
	bool checkQueFoul();
	bool isLose(); 
};

#endif