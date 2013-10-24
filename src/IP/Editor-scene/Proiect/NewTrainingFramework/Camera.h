#pragma once
#include "../Utilities/utilities.h"
class Camera 
{
public:
	Vector3 m_pos,m_rot;
	Matrix m_world,m_view,m_perspective;
	float nearc,farc,fovc;
	void moveForward(float);
	void moveBack(float);
	void moveLeft(float);
	void moveRight(float);
	void moveUp(float);
	void moveDown(float);
	void RotUp(float);
	void RotDown(float);
	void RotLeft(float);
	void RotRight(float);
	void calculateViewMatrix();
	void calculateWorldMatrix();
	void Init(float,float,float);
	~Camera();
};