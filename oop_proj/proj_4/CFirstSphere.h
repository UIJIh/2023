#ifndef _CFIRSTSPHERE_
#define _CFIRSTSPHERE_
#include "CSphere.h"

class CFirstSphere : public CSphere 
{
private:
	BallType firstBallType;
public :
	CFirstSphere(const char* ballImageName);
	BallType getFirstBallType() const noexcept;
	void setFirstBallType(BallType balltype) noexcept;
	void hitBy(CSphere& ball) noexcept;
};
#endif;
