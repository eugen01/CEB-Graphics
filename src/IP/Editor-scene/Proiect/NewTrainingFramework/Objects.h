#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture2D.h"
#include "Vertex.h"
#include "TextureCube.h"
class Object {
public:
	int id;
	Model* m_pModel;
	int m_nr2DTextures;
	Texture2D** m_p2DTextures;
	int m_nrCubeTextures;
	TextureCube** m_pCubeTextures;
	Shaders* m_pShader;
	Vector3 m_pos,m_rot,m_scale;
	int nrotherdata;
	float* m_pOtherData;
	Matrix m_world;
	void ComputeWorldMatrix();
	void Draw(Matrix,Matrix,float,float);
	
};