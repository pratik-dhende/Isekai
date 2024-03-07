#ifndef _CAMERA_H_
#define _CAMERA_H_

#include<DirectXMath.h>
using namespace DirectX;

class Camera {
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void setPosition(float, float, float);
	void setRotation(float, float, float);

	XMFLOAT3 getPosition();
	XMFLOAT3 getRotation();

	void render();
	void getViewMatrix(XMMATRIX&);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ; // In degrees.
	XMMATRIX m_viewMatrix;
};
#endif