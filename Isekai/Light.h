#ifndef _LIGHT_H_
#define _LIGHT_H_

#include<DirectXMath.h>
using namespace DirectX;

class Light {
public:
	Light();
	Light(const Light& other);
	~Light();

	void setDiffuseColor(float, float, float, float);
	void setDirection(float, float, float);

	XMFLOAT4 getDiffuseColor();
	XMFLOAT3 getDirection();

private:
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
};
#endif
