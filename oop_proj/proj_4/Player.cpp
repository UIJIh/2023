#include "Player.h"

Player::Player(unsigned int playerID){
	this->playerID = playerID;
	this->playerBallNum = 0;
	this->playerBallType = BallType::QUE;
}

void Player::setPlayerBall(unsigned int numBall) {
	this->playerBallNum = numBall;
}

unsigned int Player::getPlayerBallNum() const {
	return playerBallNum;
}

unsigned int Player::getPlayerId() const {
	return this->playerID;
}

BallType Player::getPlayerBallType() const {
	return this->playerBallType;
}

void Player::setPlayerBallType(BallType ballType) {
	this->playerBallType = ballType;
}