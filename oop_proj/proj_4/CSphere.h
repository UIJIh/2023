#ifndef _CSPHERE_
#define _CSPHERE_

#include "d3dUtility.h"
#include "Player.h"
#include "string"

using std::string;

class CSphere 
{
protected:
	typedef CSphere super;

	float center_x, center_y, center_z;
	float m_radius;
	float m_velocity_x;
	float m_velocity_z;
	float pre_center_x, pre_center_z; // previous (used when collision)
	
	int disableTurn = -1;

	string ballImageName = string();
	BallType ballType;
	IDirect3DTexture9* Tex = nullptr;
	D3DXMATRIX ballRoll;
	D3DXMATRIX m_mLocal;
	D3DMATERIAL9 m_mtrl; // material
	ID3DXMesh* m_pSphereMesh; // 3d
	LPD3DXMESH _createMappedSphere(IDirect3DDevice9* pDev);


public:
	CSphere(void);
	CSphere(const char* ballImageFileName);
	virtual ~CSphere(void);
	static const float ballRadius;

	bool create(IDirect3DDevice9* pDevice);
	void destroy(void);
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(CSphere& ball); 
	void hitBy(CSphere& ball); 
	void ballUpdate(float timeDiff);
	double getVelocity_X();
	double getVelocity_Z();
	void setPower(double vx, double vz);
	float getRadius(void) const;
	BallType getBallType() const;
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	D3DXVECTOR3 getPosition() const;
	void adjustPosition(CSphere& ball);
	void setPosition(float x, float y, float z);
	double CSphere::getPreCenter_x() const;
	double CSphere::getPreCenter_z() const;


	void deactivate() noexcept; 
	void activate() noexcept;  
	int getDisableTurn() const noexcept; 
	bool disabled() const noexcept; // ball deactivate or not?
};

#endif