#include "TurnManager.h"
#include "Status.h"
#include "CFirstSphere.h"
#include <array>

using std::array;

extern Status status;
extern array<CSphere*, 16> g_sphere;
extern Player players[2];

TurnManager::TurnManager(const vector<int>& playerIdList) { // initializing index
	this->playerIdList = playerIdList;
	this->nowTurnPlayerIndex = 0;
}

bool TurnManager::turnFinished(const array<CSphere*, 16>& fieldBalls) {
	if (!status.getTurnProgressStatus()) {
		return false;
	}
	for (unsigned int i = 0; i < fieldBalls.size(); i++) {
		CSphere ball = *(fieldBalls.at(i));

		if (abs(ball.getVelocity_X()) > 0.01 || abs(ball.getVelocity_Z()) > 0.01) {
			return false;
		}
	}
	return true;
}

void TurnManager::resetTurn() {
	status.setTurnChangeStatus(false);
	status.setTurnPlayer(this->playerIdList.at(this->nowTurnPlayerIndex));
	this->processTriggerOff();
}

void TurnManager::finishTurn() { // turn
	status.setTurnChangeStatus(true);
	this->nowTurnPlayerIndex = (this->nowTurnPlayerIndex + 1) % this->playerIdList.size();
	status.setTurnPlayer(this->playerIdList.at(this->nowTurnPlayerIndex));
	this->processTriggerOff();
}

void TurnManager::processTriggerOff() {
	status.nextTurnCount();
	status.setTurnProgressStatus(false);
	//dynamic_cast<CHandSphere&>(*g_sphere[0]).setFirstHitBallType(BallType::NONE);
}

void TurnManager::processTriggerOn() {
	//dynamic_cast<CHandSphere&>(*g_sphere[0]).setFirstHitBallType(BallType::NONE);
	status.setFoulStatus(false);
	status.setTurnProgressStatus(true);
	status.setTurnChangeStatus(false);
}

void TurnManager::setPlayerBallNum() {
	int myTakenBall = 0;
	int otherTakenBall = 0;

	for (int i = 0; i < 16; i++) {
		if (g_sphere[i]->disabled()) {
			if (g_sphere[i]->getBallType() == status.getTurnPlayer()->getPlayerBallType()) {
				myTakenBall++;
			}
			else {
				otherTakenBall++;
			}
		}
	}

	if (myTakenBall == 7 && g_sphere[8]->disabled()) {
		status.setWinnerPlayer(this->playerIdList[this->nowTurnPlayerIndex]);
	}

	Player* a = status.getTurnPlayer();
	a->setPlayerBall(myTakenBall);
	status.getNotTurnPlayer()->setPlayerBall(otherTakenBall);
}

bool TurnManager::turnProcess(const array<CSphere*, 16>& fieldBalls) {
	this->setPlayerBallNum();

	if (!this->turnFinished(fieldBalls) || status.getGameEndStatus()) {
		return false;
	}

	if (status.getFoulStatus() || status.getTurnPlayer()->getPlayerBallType() == BallType::QUE) {
		this->finishTurn();
	}
	else {
		bool putBall = false;

		for (int i = 0; i < 16; i++) {
			if (g_sphere[i]->getDisableTurn() == status.getCurrentTurnCount()
				&& g_sphere[i]->getBallType() == status.getTurnPlayer()->getPlayerBallType()) {
				putBall = true;
			}
		}

		if (putBall) {
			this->resetTurn();
		}
		else {
			this->finishTurn();
		}
	}

	return true;
}