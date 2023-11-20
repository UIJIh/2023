#ifndef _CBORDER_
#define _CBORDER_

#include "d3dUtility.h"
#include <vector>

// -----------------------------------------------------------------------------
// CBorder class definition
// �籸��(����)�� �׵θ��� ������ Ŭ������ ���� ���� (3ds max�� maya�� �۾�)
// -----------------------------------------------------------------------------
class CBorder 
{
private:
	float m_width;
	float m_depth;
	float center_x, center_y, center_z;
	D3DMATERIAL9 m_mtrl;
	D3DXMATRIX              m_mLocal;
	ID3DXMesh* mesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	ID3DXMesh* m_pBoundMesh;
	void setLocalTransform(const D3DXMATRIX& mLocal);
public:
	CBorder(D3DXCOLOR color); // �׵θ��� ������
	~CBorder(); // �׵θ��� �Ҹ���
	void setPosition(float x, float y, float z);
	bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color); // �׵θ��� ȭ�鿡 ������
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld); // �׵θ��� ȭ�鿡 �׷���
	void destroy(); // �׵θ��� ȭ�鿡�� �Ҹ��Ŵ
};

#endif
