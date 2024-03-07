#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <Directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

class ColorShader {
private:
	struct MatrixBuffer {
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ColorShader();
	ColorShader(const ColorShader&);
	~ColorShader();

	bool initialize(ID3D11Device*, HWND);
	void shutdown();
	bool render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool initializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void shutdownShader();
	void outputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool setShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
	void renderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif
