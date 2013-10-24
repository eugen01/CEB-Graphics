#pragma once
#include "../Utilities/utilities.h"
#include "Texture2D.h"
class TextureCube
{
public:
	char mfile[260];
	GLuint m_TexHandle;
	WRAPPING m_wrapping;
	int id;
	TextureCube();
	void InitCubeTexture();
	char* ExtractFace(int,int,char*,int,int);
	~TextureCube();
};