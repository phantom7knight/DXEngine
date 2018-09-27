#pragma once
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&	);
	~LightClass();


	void SetDiffuseColor(float, float, float, float);
	void SetAmbientColor(float, float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularPower(float power);

	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();
	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetSpecularColor();
	float	 GetSpecularPower();

private:

	XMFLOAT3 m_direction;
	XMFLOAT4 m_diffusecolor;
	XMFLOAT4 m_ambientcolor;
	XMFLOAT4 m_specularcolor;
	float	 m_specularpower;

};

