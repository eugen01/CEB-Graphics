#include <stdafx.h>
#include "RM.h"
#include "../Utilities/memDbg.h"

Model* RManager::GetModelbyID(int ID) {
	for(int i = 0 ; i < nrModels ; i++)
		if(pModels[i].id == ID) {
			return &pModels[i];
		}
	return NULL;
}
Texture2D* RManager::GetTexture2DbyID(int ID) {
	for(int i = 0 ; i < nr2DTextures ; i++)
		if(p2DTextures[i].id == ID) {
			return &p2DTextures[i];
		}
	return NULL;
}
TextureCube* RManager::GetTextureCubebyID(int ID) {
	for(int i = 0 ; i < nrCubeTextures ; i++)
		if(pCubeTextures[i].id == ID) {
			return &pCubeTextures[i];
		}
	return NULL;
}
Shaders* RManager::GetShaderbyID(int ID) {

	for(int i = 0 ; i < nrShaders ; i++)
		if(pShaders[i].id == ID) {
			
			return &pShaders[i];
		}
	return NULL;
}
void RManager::Init() {
	FILE *f;
	errno_t err = fopen_s(&f,"../RM.txt","r");
	char wrap[30];
	char state[30];
	
	if(err)
		printf_s("nu s-a deschis\n");
	else {
		fscanf_s( f, "#MODELS\nNRMODELS %d\n",&nrModels);
		pModels = new Model[nrModels];
		for(int i = 0 ; i < nrModels ; i++) {
			
			fscanf_s( f, "ID %d\n",&pModels[i].id);
			fscanf_s( f, "FILE %s\n",pModels[i].mfile,260);
			pModels[i].LoadModel();
		
		}
		
		fscanf_s( f, "#2DTEXTURES\nNR2DTEXTURES %d\n",&nr2DTextures);
		p2DTextures = new Texture2D[nr2DTextures];
		
		for(int i = 0 ; i < nr2DTextures ; i++) {
			fscanf_s( f, "ID %d\n",&p2DTextures[i].id);
			fscanf_s( f, "FILE %s\nWRAPPINGMODE %s\n",p2DTextures[i].mfile,260,wrap,30);
			
			if(strcmp(wrap,"REPEAT")==0)
				p2DTextures[i].m_wrapping = REPEAT;
			if(strcmp(wrap,"CLAMP_TO_EDGE")==0)
				p2DTextures[i].m_wrapping = CLAMP_TO_EDGE;
			if(strcmp(wrap,"MIRRORED_REPEAT")==0)
				p2DTextures[i].m_wrapping = MIRRORED_REPEAT;
				
			p2DTextures[i].Init2DTexture();
			
		}
		
		fscanf_s( f, "#CUBETEXTURES\nNRCUBETEXTURES %d\n",&nrCubeTextures);
		pCubeTextures = new TextureCube[nrCubeTextures];
		for(int i = 0 ; i < nrCubeTextures ; i++) {
			fscanf_s( f, "ID %d\n",&pCubeTextures[i].id);
			fscanf_s( f, "FILE %s\nWRAPPINGMODE %s\n",pCubeTextures[i].mfile,260,wrap,30);
			if(strcmp(wrap,"REPEAT")==0)
				pCubeTextures[i].m_wrapping = REPEAT;
			if(strcmp(wrap,"CLAMP_TO_EDGE")==0)
				pCubeTextures[i].m_wrapping = CLAMP_TO_EDGE;
			if(strcmp(wrap,"MIRRORED_REPEAT")==0)
				pCubeTextures[i].m_wrapping = MIRRORED_REPEAT;
			pCubeTextures[i].InitCubeTexture();
		
		}
		
		fscanf_s( f, "#SHADERS\nNRSHADERS %d\n",&nrShaders);
		pShaders = new Shaders[nrShaders];
		for( int i = 0 ; i < nrShaders ; i++) {
		
			fscanf_s( f, "ID %d\n",&pShaders[i].id);
			fscanf_s( f, "FILE %s\n",pShaders[i].fileVS,260);
			fscanf_s( f, "FILE %s\n",pShaders[i].fileFS,260);
			pShaders[i].Init();
			//TODO NRStates
			fscanf_s( f, "NRSTATES %d\n",&pShaders[i].nrstates);
			pShaders[i].states = new GLint[pShaders[i].nrstates];
			for (int j=0;j<pShaders[i].nrstates;j++) {
				fscanf_s( f, "%s\n",state,30);
				if(strcmp(state,"ALPHABLENDING")==0)
					pShaders[i].states[0] = 1;
			}
		}
		
		
	}

	fclose(f);
}
RManager* RManager::ms_pRManager;
RManager* RManager::GetInstance()
{
	if(ms_pRManager == NULL) {
		ms_pRManager = new RManager();
	}
	return ms_pRManager;
}
void RManager::DestroyInstance() 
{
	if(ms_pRManager) {
		delete ms_pRManager;
		ms_pRManager = NULL;
	}
}
RManager::RManager() 
{

}
RManager::~RManager() 
{
	delete[] pShaders;
	delete[] pModels;
	delete[] p2DTextures;
	delete[] pCubeTextures;
}