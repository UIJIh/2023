//#include "d3dUtility.h"
//
//#include <vector>
//#include <ctime>
//#include <cstdlib>
//#include <cstdio>
//#include <cassert>
//#include <array>
//
//#include "CSphere.h"
//#include "Status.h"
//#include "DisplayManager.h"
//#include "FoulManager.h"
//#include "d3dUtility.h"
//
//using std::array;
//
//extern Status status;
//extern array<CSphere*, 16> g_sphere;
//
//
//LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	static bool wire = false;
//	static bool isReset = true;
//	static int old_x = 0;
//	static int old_y = 0;
//	double dx = 0.05f;
//	double dy = 0.05f;
//	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;
//	D3DXVECTOR3 coord3d = g_sphere[0]->getPosition();
//
//	switch (msg) {
//		if (status.getFoulStatus() && !(status.getTurnProgressStatus())) {
//			switch (wParam) {
//			case VK_RIGHT:
//				g_sphere[0]->setPosition(coord3d.x + dx, coord3d.y, coord3d.z);
//				move = WORLD_MOVE;
//				break;
//			case VK_LEFT:
//				g_sphere[0]->setPosition(coord3d.x - dx, coord3d.y, coord3d.z);
//				move = WORLD_MOVE;
//				break;
//			case VK_UP:
//				g_sphere[0]->setPosition(coord3d.x, coord3d.y, coord3d.z + dx);
//				move = WORLD_MOVE;
//				break;
//			case VK_DOWN:
//				g_sphere[0]->setPosition(coord3d.x, coord3d.y, coord3d.z - dx);
//				move = WORLD_MOVE;
//				break;
//			}
//		}
//	}
//	return ::DefWindowProc(hwnd, msg, wParam, lParam);
//}