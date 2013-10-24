#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
#include "Texture2D.h"
#include "Camera.h"
class Model 
{
public:
	int id;
	GLint m_nrVertex, m_nrIndici;
	
	GLuint m_VertexBuffer,m_IndexBuffer;
	char mfile[260];
	Model();
	void LoadModel();
	void InitModel(Shaders&, Texture2D&, Camera& );
	~Model();
}; 
