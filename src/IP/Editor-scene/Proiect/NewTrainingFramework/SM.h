#pragma once
#include "../Utilities/utilities.h"
#include "Camera.h"
#include "Objects.h"
#include "Light.h"
class SManager
{
protected:
	SManager();
	~SManager();
	SManager(const SManager&);
	SManager& operator=(const SManager&);
	static SManager *ms_pSManager;
public:
	static SManager* GetInstance();
	static void DestroyInstance();
	int nrObjects;
	Object *pObjects;
	Camera *pCam;
	int nrLights;
	Light *m_pLights;
	Vector3 ambientcolor; 
	void Init();
	void Update();
	void Draw(float,float);
};