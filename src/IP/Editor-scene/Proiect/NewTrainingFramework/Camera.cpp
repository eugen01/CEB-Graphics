#include <stdafx.h>
#include "Camera.h"
#include "Globals.h"
#include "../Utilities/memDbg.h"
GLfloat X_LIMIT = 1.57079633f;
GLfloat movespeed=300.f;
GLfloat rotspeed=1.f;
Camera::~Camera() {
}
void Camera::calculateWorldMatrix()
{
	Matrix rx,ry,rz;
	rz.SetRotationZ(m_rot.z);
	rx.SetRotationX(m_rot.x);
	ry.SetRotationY(m_rot.y);
	Matrix t;
	t.SetIdentity();
	t.SetTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_world = rz*rx*ry*t;
	
}
void Camera::calculateViewMatrix()
{
	Matrix t;
	t.SetIdentity();
	
	t.m[3][0] = -m_pos.x;
	t.m[3][1] = -m_pos.y;
	t.m[3][2] = -m_pos.z;

	Matrix ry,rx,rz,r;
	
	ry.SetRotationY(-m_rot.y);
	rx.SetRotationX(-m_rot.x);
	rz.SetRotationZ(-m_rot.z);

	
	r = ry * rx * rz;

	m_view = t * r;
}
void Camera::Init(float fovcam,float nearcam,float farcam)
{
	m_perspective.SetPerspective(fovcam, (float)((float)Globals::screenWidth/Globals::screenHeight), nearcam, farcam);
	m_pos = Vector3(0.f, 0.f, 300.f);
	nearc = nearcam;
	farc = farcam;
	fovc = fovcam;
	m_view.SetIdentity();
	m_rot = Vector3(0.f, 0.f, 0.f);
	
	
}
void Camera::moveForward(float deltaTime)
{

	Vector4 movelocal = Vector4(0.f, 0.f, -deltaTime*movespeed, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
    calculateViewMatrix();

}
void Camera::moveBack(float deltaTime)
{

	Vector4 movelocal = Vector4(0.f, 0.f, deltaTime*movespeed, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
	calculateViewMatrix();
}
void Camera::moveLeft(float deltaTime)
{

	Vector4 movelocal = Vector4(-deltaTime*movespeed, 0.f, 0.f, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
	calculateViewMatrix();
	
}
void Camera::moveRight(float deltaTime)
{

	Vector4 movelocal = Vector4(deltaTime * movespeed, 0.f, 0.f, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
	calculateViewMatrix();
}
void Camera::moveUp(float deltaTime)
{

	Vector4 movelocal = Vector4(0.f, deltaTime*movespeed, 0.f, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
	calculateViewMatrix();
}
void Camera::moveDown(float deltaTime)
{

	Vector4 movelocal = Vector4(0.f, -deltaTime*movespeed, 0.f, 1.f);
	calculateWorldMatrix();
	Vector4 moveworld = movelocal * m_world;
	m_pos = Vector3(moveworld.x, moveworld.y, moveworld.z);
	calculateViewMatrix();
}
void Camera::RotDown(float deltaTime)
{
	if(m_rot.x - deltaTime*rotspeed > -X_LIMIT)
		m_rot.x += -deltaTime*rotspeed;
	else
		m_rot.x = -X_LIMIT;
	calculateViewMatrix();
}
void Camera::RotUp(float deltaTime)
{
	if(m_rot.x + deltaTime*rotspeed < X_LIMIT)
		m_rot.x += deltaTime*rotspeed;
	else
		m_rot.x = X_LIMIT;
	calculateViewMatrix();
}
void Camera::RotLeft(float deltaTime)
{
	m_rot.y += deltaTime*rotspeed;
	calculateViewMatrix();
}
void Camera::RotRight(float deltaTime)
{
	m_rot.y += -deltaTime*rotspeed;
	calculateViewMatrix();
}