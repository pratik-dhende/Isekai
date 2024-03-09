#ifndef _LIGHT_H_
#define _LIGHT_H_

#include<DirectXMath.h>
using namespace DirectX;

class Light {
public:
	Light();
	Light(const Light& other);
	~Light();

	void setAmbientColor(float, float, float, float);
	void setDiffuseColor(float, float, float, float);
	void setDirection(float, float, float);
	void setSpecularColor(float, float, float, float);
	void setSpecularPower(float);

	XMFLOAT4 getAmbientColor();
	XMFLOAT4 getDiffuseColor();
	XMFLOAT3 getDirection();
	XMFLOAT4 getSpecularColor();
	float getSpecularPower();

private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
	XMFLOAT4 m_specularColor;
	float m_specularPower;
};
#endif
