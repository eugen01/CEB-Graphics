#include <stdafx.h>
#include "Shaders.h"
#include "../Utilities/memDbg.h"
int Shaders::Init()
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVS);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFS);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionLoc = glGetAttribLocation(program, "a_posL");
	texCoordLoc = glGetAttribLocation ( program, "a_texCoord" );
	sampler2DLoc = glGetUniformLocation ( program, "s_Texture2D" );
	matrixwvpLoc = glGetUniformLocation(program, "u_wvp");
	samplerCubeLoc = glGetUniformLocation(program, "s_TextureCube");
	normalLoc = glGetAttribLocation(program, "a_normL");
	tangentLoc = glGetAttribLocation(program, "a_tanL");
	binormLoc = glGetAttribLocation(program, "a_binormL");
	normalMapLoc = glGetUniformLocation(program, "s_NormalMap");
	camLoc = glGetUniformLocation(program, "u_camw");
	matrixwLoc = glGetUniformLocation(program, "u_w");
	tillingfactorLoc = glGetUniformLocation(program, "u_fTillingFactor");
	sGrassLoc = glGetUniformLocation(program, "u_sGrass");
	sRockLoc = glGetUniformLocation(program, "u_sRock");
	sDirtLoc = glGetUniformLocation(program, "u_sDirt");
	sBlendMapLoc = glGetUniformLocation(program, "u_sBlendMap");
	StartFogLoc = glGetUniformLocation(program,"u_fStartFog");
	RangeFogLoc = glGetUniformLocation(program, "u_fRangeFog");
	FogColorLoc = glGetUniformLocation(program, "u_vFogColor");
	dirlightLoc = glGetUniformLocation(program, "u_dirlight");
	dirsourcecolorLoc = glGetUniformLocation(program, "u_dirsourcecolor");
	ambientalLoc = glGetUniformLocation(program, "u_ambiental");
	blendingcountLoc = glGetUniformLocation(program, "blendingcount");
	specularpowerLoc = glGetUniformLocation(program, "u_specularpower");
	pointlightpos1Loc = glGetUniformLocation(program, "u_pointsourcecolor1");
	pointlightcolor1Loc = glGetUniformLocation(program, "u_pointcolor1");
	pointlightpos2Loc= glGetUniformLocation(program, "u_pointsourcecolor2");
	pointlightcolor2Loc = glGetUniformLocation(program, "u_pointcolor2");
	sBottomWaterLoc = glGetUniformLocation(program, "s_Bottom");
	sDispMapLoc = glGetUniformLocation(program, "u_dispmap");
	sFireMaskLoc = glGetUniformLocation(program, "u_firemask");
	timeLoc = glGetUniformLocation(program, "u_time");
	
	a_posNLoc = glGetAttribLocation(program, "a_posN");
	a_uvLoc = glGetAttribLocation(program, "a_uv");
	u_texColor1Loc = glGetUniformLocation(program, "u_texColor1");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}