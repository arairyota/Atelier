#ifndef MAIN_H
#define MAIN_H


#define _CRT_SECURE_NO_WARNINGS
#define INIT_SCALE (XMFLOAT3(1.0f, 1.0f, 1.0f))
#define INIT_ROTATION (XMFLOAT3(0.0f, 0.0f, 0.0f))
#define INIT_SCALE2D (XMFLOAT2(1.0f, 1.0f))
#define INIT_ROTATION2D (XMFLOAT2(0.0f, 0.0f))

#include <stdio.h>
#include <windows.h>
#include <assert.h>

#include <typeinfo>
#include <vector>
#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#pragma comment(lib, "assimp.lib")

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")


#define SCREEN_WIDTH	(1920)			// ウインドウの幅
#define SCREEN_HEIGHT	(1080)			// ウインドウの高さ


HWND GetWindow();

#endif // !MAIN_H
