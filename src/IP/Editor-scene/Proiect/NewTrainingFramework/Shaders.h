#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	int id;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint nrstates;
	GLint *states;
	GLint positionLoc;
	GLint matrixwvpLoc;
	GLint sampler2DLoc;
	GLint texCoordLoc;
	GLint samplerCubeLoc;
	GLint normalMapLoc;
	GLint sBottomWaterLoc;
	GLint sDispMapLoc, sFireMaskLoc;
	GLint timeLoc; 
	GLint normalLoc, tangentLoc, binormLoc;
	GLint camLoc;
	GLint matrixwLoc;
	GLint tillingfactorLoc;
	GLint sGrassLoc, sDirtLoc, sRockLoc, sBlendMapLoc;
	GLint StartFogLoc, RangeFogLoc, FogColorLoc;
	GLint dirlightLoc, dirsourcecolorLoc, ambientalLoc, blendingcountLoc, specularpowerLoc;
	GLint pointlightpos1Loc, pointlightpos2Loc, pointlightcolor1Loc, pointlightcolor2Loc;
	GLint a_posNLoc,a_uvLoc,u_texColor1Loc;
	int Init();
	~Shaders();
};