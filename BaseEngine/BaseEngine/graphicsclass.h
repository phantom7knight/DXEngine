#pragma once
#ifndef GRAPHICSCLASS_H_
#define GRAPHICSCLASS_H_

#include <Windows.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"

#include "textureshaderclass.h"
#include "colorshaderclass.h"
#include "LightShaderClass.h"
#include "LightClass.h"


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	void Update();

	bool Initialize(int, int, HWND, XMFLOAT3 );
	void Shutdown();
	bool Frame();

	float Camera_PosX ;
	float Camera_PosY ;
	float Camera_PosZ ;

private:
	bool Render(float);

	D3DClass*	 m_D3D;
	CameraClass* m_Camera;
	ModelClass*  m_Model;
	ColorShaderClass* m_ColorShader;
	InputClass* m_Input;

	TextureShaderClass* m_TextureShader;

	LightClass* m_Light;
	LightShaderClass* m_LightShader;


};

#endif // !GRAPHICSCLASS_H_

