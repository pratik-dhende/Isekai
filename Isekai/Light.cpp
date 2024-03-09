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

void Light::setSpecularColor(float red, float green, float blue, float alpha)
{
    m_specularColor = XMFLOAT4(red, green, blue, alpha);
}

void Light::setSpecularPower(float power)
{
    m_specularPower = power;
}

void Light::setPosition(float x, float y, float z)
{
    m_position = XMFLOAT4(x, y, z, 1.0f);
    return;
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

XMFLOAT4 Light::getSpecularColor()
{
    return m_specularColor;
}

float Light::getSpecularPower()
{
    return m_specularPower;
}
    
XMFLOAT4 Light::getPosition()
{
    return m_position;
}
