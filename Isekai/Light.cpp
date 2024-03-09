#include "Light.h"

Light::Light() {

}


Light::Light(const Light& other) {

}


Light::~Light() {

}

void Light::setAmbientColor(float red, float green, float blue, float alpha) {
    m_ambientColor = XMFLOAT4(red, green, blue, alpha);
}

void Light::setDiffuseColor(float red, float green, float blue, float alpha) {
    m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
}


void Light::setDirection(float x, float y, float z) {
    m_direction = XMFLOAT3(x, y, z);
}

XMFLOAT4 Light::getAmbientColor() {
    return m_ambientColor;
}

XMFLOAT4 Light::getDiffuseColor() {
    return m_diffuseColor;
}


XMFLOAT3 Light::getDirection() {
    return m_direction;
}