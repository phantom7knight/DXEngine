#pragma once




//Library includes

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma commend(lib, "d3dcompiler.lib")

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace std;
using namespace DirectX;

#define BT_NO_SIMD_OPERATOR_OVERLOADS

//File Includes

#include "systemclass.h"
#include "graphicsclass.h"
#include "inputclass.h"


//Constants

#define Safe_Release(ptr) { ptr->Release();   ptr = 0; }


//Game Consants

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.1f;
const float SCREEN_DEPTH = 1000.0f;

#define ScreeWidth		800
#define ScreenHeight	500

#define  PI_	3.14


// Position of all the data stuff
// ../BaseEngine/data/Shaders/	