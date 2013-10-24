// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "RM.h"
#include "SM.h"
#include "Model.h"
#include "Camera.h"


GLuint vboId[2];
Shaders myShaders;
GLfloat rot=1.f;
Matrix rotationMatrix;
GLint x;
Model model;
Texture2D tex;
float time;
float dtime;
short int Globals::keypressed=0;
short int Globals::effectpressed=0;

int Init ( ESContext *esContext )
{
	
	glClearColor(1,1,1,1);
	glEnable(GL_DEPTH_TEST);
	glClearDepthf(1.0);
	RManager::GetInstance()->Init();
	SManager::GetInstance()->Init();
	return 0;
	
}


void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	SManager::GetInstance()->Draw(time,dtime);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, GLfloat deltaTime )
{
	dtime = deltaTime;
	time += deltaTime;
	if(Globals::keypressed & (1<<Globals::moveF))
		SManager::GetInstance()->pCam->moveForward(deltaTime);
	if(Globals::keypressed & (1<<Globals::moveB))
		SManager::GetInstance()->pCam->moveBack(deltaTime);
	if(Globals::keypressed & (1<<Globals::moveL))
		SManager::GetInstance()->pCam->moveLeft(deltaTime);
	if(Globals::keypressed & (1<<Globals::moveR))
		SManager::GetInstance()->pCam->moveRight(deltaTime);
	if(Globals::keypressed & (1<<Globals::moveU))
		SManager::GetInstance()->pCam->moveUp(deltaTime);
	if(Globals::keypressed & (1<<Globals::moveD))
		SManager::GetInstance()->pCam->moveDown(deltaTime);
	if(Globals::keypressed & (1<<Globals::rotU))
		SManager::GetInstance()->pCam->RotUp(deltaTime);
	if(Globals::keypressed & (1<<Globals::rotD))
		SManager::GetInstance()->pCam->RotDown(deltaTime);
	if(Globals::keypressed & (1<<Globals::rotL))
		SManager::GetInstance()->pCam->RotLeft(deltaTime);
	if(Globals::keypressed & (1<<Globals::rotR))
		SManager::GetInstance()->pCam->RotRight(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{

	if(bIsPressed) {
		
		switch(key) {
			
			case 'W':
				Globals::keypressed|=1<<Globals::moveF;
				break;
			case 'S':
				Globals::keypressed|=1<<Globals::moveB;
				break;
			case 'A':
				Globals::keypressed|=1<<Globals::moveL;
				break;
			case 'D':
				Globals::keypressed|=1<<Globals::moveR;
				break;
			case 'R':
				Globals::keypressed|=1<<Globals::moveU;
				break;
			case 'F':
				Globals::keypressed|=1<<Globals::moveD;
				break;
			case '&':
				Globals::keypressed|=1<<Globals::rotU;
				break;
			case '(':
				Globals::keypressed|=1<<Globals::rotD;
				break;
			case '\'':
				Globals::keypressed|=1<<Globals::rotR;
				break;
			case '%':
				Globals::keypressed|=1<<Globals::rotL;
				break;
			case 'I':
				SManager::GetInstance()->pObjects[0].m_pos.x += 4;
				break;
			case 'K':
				SManager::GetInstance()->pObjects[0].m_pos.x -= 4;
				break;
			case 'J':
				SManager::GetInstance()->pObjects[0].m_pos.y += 4;
				break;
			case 'L':
				SManager::GetInstance()->pObjects[0].m_pos.y -= 4;
				break;
			default:
				break;
			}
		}
	else {
		switch(key) {
			case 'W':
				Globals::keypressed&=~(1<<Globals::moveF);
				break;
			case 'S':
				Globals::keypressed&=~(1<<Globals::moveB);
				break;
			case 'A':
				Globals::keypressed&=~(1<<Globals::moveL);
				break;
			case 'D':
				Globals::keypressed&=~(1<<Globals::moveR);
				break;
			case 'R':
				Globals::keypressed&=~(1<<Globals::moveU);
				break;
			case 'F':
				Globals::keypressed&=~(1<<Globals::moveD);
				break;
			case '&':
				Globals::keypressed&=~(1<<Globals::rotU);
				break;
			case '(':
				Globals::keypressed&=~(1<<Globals::rotD);
				break;
			case '\'':
				Globals::keypressed&=~(1<<Globals::rotR);
				break;
			case '%':
				Globals::keypressed&=~(1<<Globals::rotL);
				break;
			default:
				break;
			}
		}
		
}
void CleanUp()
{
	glDeleteBuffers(2, vboId);
	SManager::DestroyInstance();
	RManager::DestroyInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "3D Scene Editor", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

