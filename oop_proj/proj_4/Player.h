#ifndef _PLAYER_
#define _PLAYER_

enum class BallType
{
	QUE,   // 0
	SOLID,
	BLACK, // 8
	STRIPE,
	NONE
};

class Player
{
private:
	unsigned int playerID; 
	unsigned int playerBallNum; 

	BallType playerBallType; 

public:
	Player(unsigned int playerID);
	void setPlayerBall(unsigned int ballNum); 
	unsigned int getPlayerBallNum() const; 
	unsigned int getPlayerId() const; 

	BallType getPlayerBallType() const; 
	void setPlayerBallType(BallType ballType); 
};

#endif