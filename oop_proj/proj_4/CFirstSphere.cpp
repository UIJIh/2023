#include "CFirstSphere.h"

CFirstSphere::CFirstSphere(const char* ballImageName) : CSphere("0") {
	this->firstBallType = BallType::NONE;
}

BallType CFirstSphere::getFirstBallType() const noexcept { 
	return this->firstBallType;
}

void CFirstSphere::setFirstBallType(BallType ballType) noexcept {
	this->firstBallType = ballType;
}

void CFirstSphere::hitBy(CSphere& ball) noexcept {
	if (this->hasIntersected(ball)) {
		if (this->firstBallType == BallType::NONE) {
			this->firstBallType = ball.getBallType();
		}
		super::hitBy(ball);
	}
}
