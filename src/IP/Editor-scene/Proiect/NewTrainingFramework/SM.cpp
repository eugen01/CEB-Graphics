#include <stdafx.h>
#include "SM.h"
#include "RM.h"
#include "Camera.h"
#include "Light.h"
#include "../Utilities/memDbg.h"

void SManager::Init() 
{
	float farc,nearc,fovc;
	int modelID,text2DID,shadID,textCubeID;
	FILE *f;
	errno_t err = fopen_s(&f,"../SM.txt","r");
	pCam = new Camera();
	char moving[30];
	char type[30];
	
	if(err)
		printf_s("nu s-a deschis\n");
	else {
		fscanf_s( f, "#OBJECTS\nNROBJECTS %d\n",&nrObjects);
		pObjects = new Object[nrObjects];
		for ( int i = 0 ; i < nrObjects ; i++) {
			fscanf_s( f, "ID %d\n",&pObjects[i].id);
			fscanf_s( f, "MODEL ID %d\n",&modelID); 
			pObjects[i].m_pModel = RManager::GetInstance()->GetModelbyID(modelID);
			
			fscanf_s( f, "NR2DTEXTURES %d\n",&pObjects[i].m_nr2DTextures);
			pObjects[i].m_p2DTextures = new Texture2D*[pObjects[i].m_nr2DTextures];
		
			for(int j = 0 ; j < pObjects[i].m_nr2DTextures; j++) {
				fscanf_s( f, "TEXTURE2D ID %d\n",&text2DID); 
				pObjects[i].m_p2DTextures[j] = RManager::GetInstance()->GetTexture2DbyID(text2DID);
			
			}
			
			fscanf_s( f, "NRCUBETEXTURES %d\n",&pObjects[i].m_nrCubeTextures);
			pObjects[i].m_pCubeTextures = new TextureCube*[pObjects[i].m_nrCubeTextures];
			for(int j = 0 ; j < pObjects[i].m_nrCubeTextures; j++) {
				fscanf_s( f, "TEXTURECUBE ID %d\n",&textCubeID); 
				pObjects[i].m_pCubeTextures[j] = RManager::GetInstance()->GetTextureCubebyID(textCubeID);
			}
			
			fscanf_s( f, "SHADER ID %d\n",&shadID);
			pObjects[i].m_pShader = RManager::GetInstance()->GetShaderbyID(shadID);
		
			
			fscanf_s( f, "POS %f,%f,%f\n",&pObjects[i].m_pos.x, &pObjects[i].m_pos.y, &pObjects[i].m_pos.z);
			fscanf_s( f, "ROT %f,%f,%f\n",&pObjects[i].m_rot.x, &pObjects[i].m_rot.y, &pObjects[i].m_rot.z);
			fscanf_s( f , "SCALE %f,%f,%f\n",&pObjects[i].m_scale.x, &pObjects[i].m_scale.y, &pObjects[i].m_scale.z);
			pObjects[i].ComputeWorldMatrix();
			
			fscanf_s( f, "NROTHERDATA %d\n",&pObjects[i].nrotherdata);
			pObjects[i].m_pOtherData = new float[pObjects[i].nrotherdata];
		
			for(int j = 0 ; j < pObjects[i].nrotherdata; j++) {
				fscanf_s( f,"%*s %f\n",&pObjects[i].m_pOtherData[j]);
			
			}
			
		}
		fscanf_s( f, "#CAMERA \nFAR %f\nNEAR %f\nFOV %f\n",&farc,&nearc,&fovc);
		pCam->Init(fovc,nearc,farc);
		
		fscanf_s( f, "#LIGHTS\nAMBIENTALA %f,%f,%f\n",&ambientcolor.x,&ambientcolor.y,&ambientcolor.z);
		fscanf_s( f, "NRLIGHTS %d\n",&nrLights);
		m_pLights = new Light[nrLights];
		for(int i = 0 ; i < nrLights ; i++) {
			fscanf_s( f , "ID %d\nCOLOR %f,%f,%f\n",&m_pLights[i].id,&m_pLights[i].color.x,&m_pLights[i].color.y,&m_pLights[i].color.z);
			fscanf_s( f , "TYPE %s\n",type,30);
		
			if (strcmp(type,"POINT") == 0) {
			fscanf_s( f , "POSITION %f,%f,%f\n",&m_pLights[i].m_pos.x,&m_pLights[i].m_pos.y,&m_pLights[i].m_pos.z); 
			fscanf_s( f , "MOVING %s\n",moving,30);
			if ( strcmp (moving,"NONE") == 0 )
				m_pLights[i].move = NONE; 
			if ( strcmp (moving,"AXISX") == 0 )
				m_pLights[i].move = AXISX;
			if ( strcmp (moving,"AXISY") == 0 )
				m_pLights[i].move = AXISY;
			if ( strcmp (moving,"AXISZ") == 0 )
				m_pLights[i].move = AXISZ;
			if ( strcmp (moving,"CIRCLEX") == 0 )
				m_pLights[i].move = CIRCLEX;
			fscanf_s( f, "RADIUS %f\nSPEED %f\n",&m_pLights[i].radius,&m_pLights[i].speed);
			
			}
			if ( strcmp (type,"DIR") == 0) {
		
			m_pLights[i].m_dir.x = 1.0;
			m_pLights[i].m_dir.y = 1.0;
			m_pLights[i].m_dir.z = 1.0;
			fscanf_s( f , "DIRECTION %f,%f,%f",&m_pLights[i].m_dir.x,&m_pLights[i].m_dir.y,&m_pLights[i].m_dir.z);
		
			}
		}
		
		
	}
	
	fclose(f);

	
}
void SManager::Draw(float time,float dtime) {
	pCam->calculateViewMatrix();
	for( int i = 0 ; i < nrObjects ; i++)
		pObjects[i].Draw(pCam->m_view, pCam->m_perspective, time, dtime);
}

SManager* SManager::ms_pSManager;

SManager* SManager::GetInstance()
{
	if(ms_pSManager == NULL) {
		ms_pSManager = new SManager();
		
	}
	return ms_pSManager;
}
void SManager::DestroyInstance() 
{
	if(ms_pSManager) {
		delete ms_pSManager;
		ms_pSManager = NULL;
	}
}
SManager::SManager() 
{

}
SManager::~SManager() 
{
	delete pCam;
	for ( int i = 0 ; i < nrObjects ; i++) {
		delete[] pObjects[i].m_p2DTextures;
		delete[] pObjects[i].m_pCubeTextures;
	}
	delete[] pObjects;
	delete[] m_pLights;
	
}