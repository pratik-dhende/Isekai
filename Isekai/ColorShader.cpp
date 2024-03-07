#include "ColorShader.h"

ColorShader::ColorShader() {
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_layout = nullptr;
	m_matrixBuffer = nullptr;
}

ColorShader::ColorShader(const ColorShader& other) {

}

ColorShader::~ColorShader() {

}

bool ColorShader::initialize(ID3D11Device* device, HWND hwnd) {
	bool result;
	wchar_t vsFileName[128];
	wchar_t psFileName[128];
	int error;

	// Set the filename of the vertex shader.
	error = wcscpy_s(vsFileName, 128, L"../Isekai/color.vs");
	if (error != 0) {
		return false;
	}

	// Set the filename of the pixel shader.
	error = wcscpy_s(psFileName, 128, L"../Isekai/color.ps");
	if (error != 0) {
		return false;
	}

	// Initialize the vertex and pixel shaders.
	result = initializeShader(device, hwnd, vsFileName, psFileName);
	if (!result) {
		return false;
	}

	return true;
}

void ColorShader::shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	shutdownShader();
}

bool ColorShader::render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix) {
	bool result;

	// Set the shader parameters that it will use for rendering.
	result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result) {
		return false;
	}

	// Now render the prepared buffers with the shader.
	renderShader(deviceContext, indexCount);

	return true;
}

bool ColorShader::initializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFileName, WCHAR* psFileName) {
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Initialize the pointers this function will use to null.
	errorMessage = nullptr;
	vertexShaderBuffer = nullptr;
	pixelShaderBuffer = nullptr;

	// Compile the vertex shader code.
	result = D3DCompileFromFile(vsFileName, nullptr, nullptr, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result)) {
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, vsFileName);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else {
			MessageBox(hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = D3DCompileFromFile(psFileName, nullptr, nullptr, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result)) {
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, psFileName);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else {
			MessageBox(hwnd, psFileName, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result)) {
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
	if (FAILED(result)) {
		return false;
	}

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;


}