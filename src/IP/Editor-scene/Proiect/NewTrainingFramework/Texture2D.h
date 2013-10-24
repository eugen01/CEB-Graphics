#pragma once
#include "../Utilities/utilities.h"
enum WRAPPING
{
	REPEAT,
	CLAMP_TO_EDGE,
	MIRRORED_REPEAT
};
class Texture2D
{
public:
	int id;
	char mfile[260];
	GLuint m_TexHandle;
	WRAPPING m_wrapping;
	Texture2D();
	void Init2DTexture();
	~Texture2D();
};
