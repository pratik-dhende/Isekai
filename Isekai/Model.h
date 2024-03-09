#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

#include "Texture.h"

using namespace DirectX;
using namespace std;

class Model {
private:
	struct Vertex {
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelFormat {
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Model();
	Model(const Model& other);
	~Model();

	bool initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void shutdown();
	void render(ID3D11DeviceContext*);

	int getIndexCount();

	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void releaseTexture();

	bool loadModel(char*);
	void releaseModel();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_texture;
	ModelFormat* m_model;
};

#endif
