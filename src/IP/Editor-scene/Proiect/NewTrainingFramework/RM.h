#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture2D.h"
#include "Shaders.h"
#include "TextureCube.h"
class RManager
{
protected:
	RManager();
	~RManager();
	RManager(const RManager&);
	RManager& operator=(const RManager&);
	static RManager *ms_pRManager;
public:
	static RManager* GetInstance();
	static void DestroyInstance();
	int nrModels;
	Model* pModels; 
	int nr2DTextures;
	Texture2D* p2DTextures;
	int nrCubeTextures;
	TextureCube *pCubeTextures;
	int nrShaders;
	Shaders* pShaders;
	void Init();
	Model* GetModelbyID(int ID);
	Texture2D* GetTexture2DbyID(int ID);
	TextureCube* GetTextureCubebyID(int ID);
	Shaders* GetShaderbyID(int ID);
};