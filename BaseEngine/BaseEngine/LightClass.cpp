#include "stdafx.h"
#include "LightClass.h"


LightClass::LightClass()
{
}

LightClass::LightClass(const LightClass &)
{
}


LightClass::~LightClass()
{
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffusecolor = XMFLOAT4(red, green, blue, alpha);

	return;
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientcolor = XMFLOAT4(red, green, blue, alpha);

	return;
}

void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularcolor = XMFLOAT4(red, green, blue, alpha);

	return;
}

void LightClass::SetDirection(float X, float Y, float Z)
{
	m_direction = XMFLOAT3(X, Y, Z);

	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_specularpower = power;
}

XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffusecolor;
}

XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}

XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientcolor;
}

XMFLOAT4 LightClass::GetSpecularColor()
{
	return m_specularcolor;
}

float LightClass::GetSpecularPower()
{
	return m_specularpower;
}
