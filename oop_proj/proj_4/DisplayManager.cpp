#include "DisplayManager.h"

using std::array;

extern Status status;
extern CHole g_hole[6];
extern array<CSphere*, 16> g_sphere;

DisplayManager::DisplayManager(const int windowWidth, const int windowHeight, Player* players) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->players = players;
}

DisplayManager::~DisplayManager() {
	for (unsigned int i = 0; i < 9; i++) {
		delete this->FontObjects[i];
	}
	delete[] this->FontObjects;
}

bool DisplayManager::create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice) {
	for (unsigned int i = 0; i < 9; i++) {
		this->FontObjects[i] = new CD3DFont(fontFamily, fontSize, 0);
		this->FontObjects[i]->InitDeviceObjects(pDevice);
		this->FontObjects[i]->RestoreDeviceObjects();
	}

	this->playerName[0] = "Player " + std::to_string(this->players[0].getPlayerId());
	this->playerName[1] = "Player " + std::to_string(this->players[1].getPlayerId());

	return true;
}

void DisplayManager::destroy() {
	for (unsigned int i = 0; i < 2; i++) {
		this->FontObjects[i]->InvalidateDeviceObjects();
		this->FontObjects[i]->DeleteDeviceObjects();
		d3d::Delete<CD3DFont*>(this->FontObjects[i]);
	}
}

string DisplayManager::_getFirstBallType(const BallType b) {
	string result = "";

	switch (b) {
	case BallType::QUE: result = "";
		break;
	case BallType::SOLID: result = "<SOLID>";
		break;
	case BallType::STRIPE: result = "<STRIPE>";
		break;
	case BallType::BLACK: result = "";
		break;
	}
	return result;
}

//for (int i = 0; i < 16; i++) {
	//	if (g_sphere[i]->disabled()) {
	//		switch (g_sphere[i]->getBallType()) {
	//		case BallType::QUE:
	//			result = "QUE";
	//			break;
	//		case BallType::SOLID:
	//			result = "SOLID"; 
	//			break;
	//		case BallType::STRIPE:
	//			result = "STRIPE";
	//			break;
	//		case BallType::BLACK:
	//			result = "BLACK"; 
	//			break;
	//		}
	//	}
	//}
//string DisplayManager::_getHoleBallType() {
//	string result = "";
//	for (int i = 0; i < 6; i++) {
//		for (int j = 0; j < 16; j++) {
//			result = "test"; // 이거만 출력되고
//			CSphere& ball = *g_sphere[j]; // 여기까지 도달을 못함
//			if (g_hole[i].hasIntersected(ball) && !(ball.disabled())) {
//				BallType nowBallType = ball.getBallType();
//				result = "----";
//
//				switch (nowBallType) {
//				case BallType::QUE:
//					result = "QUE";
//					break; 
//				case BallType::SOLID:
//					result = "SOLID"; 
//					break;
//				case BallType::STRIPE:
//					result = "STRIPE";
//					break;
//				case BallType::BLACK:
//					result = "BLACK";
//					break;
//
//				}
//			}
//		}
//	}
//	return result;
//}

string DisplayManager::_getTurnStatus() {
	string result = "";

	if (status.getTurnProgressStatus() == true) {
		result = "MOVING...";
	}
	else if (status.getTurnProgressStatus() == false) {
		result = "YOUT TURN!";
	}
	return result;
}

string DisplayManager::_getFaulStatus() {
	string result = "";
	if (status.getFoulStatus() == true) {
		
		result = "MOVE THE QUE BALL!";
	}
	return result;
}

bool DisplayManager::update() {
	this->playerBallCount[0] = "Points : " + std::to_string(this->players[0].getPlayerBallNum());
	this->playerBallCount[1] = "Points : " + std::to_string(this->players[1].getPlayerBallNum());

	this->playerBallType[0] = _getFirstBallType(this->players[0].getPlayerBallType());
	this->playerBallType[1] = _getFirstBallType(this->players[1].getPlayerBallType());


	switch (status.getTurnPlayer()->getPlayerId()) {
	case 1:
		this->FontObjects[0]->DrawText(40, 20, 0xff0000FF, this->playerName[0].c_str());
		this->FontObjects[1]->DrawText(windowWidth - 230, 20, 0xff000000, this->playerName[1].c_str());
		break;

	case 2:
		this->FontObjects[0]->DrawText(40, 20, 0xff000000, this->playerName[0].c_str());
		this->FontObjects[1]->DrawText(windowWidth - 230, 20, 0xff0000FF, this->playerName[1].c_str());
		break;
	}

	this->FontObjects[2]->DrawText(40, 50, 0xff0000000, this->playerBallCount[0].c_str());
	this->FontObjects[3]->DrawText(windowWidth - 230, 50, 0xff0000000, this->playerBallCount[1].c_str());

	this->FontObjects[4]->DrawText(120, 20, 0xff0000000, this->playerBallType[0].c_str());
	this->FontObjects[5]->DrawText(windowWidth - 140, 20, 0xff0000000, this->playerBallType[1].c_str());

	if (status.getTurnProgressStatus()) {
		//this->FontObjects[6]->DrawText((windowWidth / 2) - 50, 45, 0xff0000000, _getHoleBallType().c_str());
		this->FontObjects[7]->DrawText((windowWidth / 2) - 60, 20, 0xff0000000, _getTurnStatus().c_str());
	}
	else if (!(status.getTurnProgressStatus())) {
		this->FontObjects[7]->DrawText((windowWidth / 2) - 70, 20, 0xff0000FF, _getTurnStatus().c_str());
	}

	if (status.getFoulStatus() && !(status.getTurnProgressStatus())) {
		
		this->FontObjects[8]->DrawText((windowWidth / 2) - 120, 45, 0xffff0000, _getFaulStatus().c_str()); // red
	}
	return false;
}