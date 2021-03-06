#pragma once

//===============================================
//Rendering Mode
//===============================================

//#define FWD_RENDERDING
#define DEFERRED_RENDERING

//===============================================


#include <iostream>
#include <stdlib.h>



//Library includes

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma commend(lib, "d3dcompiler.lib")

#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_5.h>
#include <DirectXMath.h>
#include <fstream>
#include <WICTextureLoader.h>

using namespace std;
using namespace DirectX;


#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>




#define BT_NO_SIMD_OPERATOR_OVERLOADS

//File Includes

#include "systemclass.h"
#include "graphicsclass.h"
#include "inputclass.h"
#include "d3dclass.h"
#include "DeferredBuffersClass.h"
#include "DeferredShaderClass.h"
#include "ScreenQuad.h"
#include "ShaderStructDefs.h"
#include "SharedDefs.h"
#include "ImguiManager.h"

//Constants

#define Safe_Release(ptr) { ptr->Release();   ptr = 0; }
#define Result_Check(result) { if(!result) return false; }

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