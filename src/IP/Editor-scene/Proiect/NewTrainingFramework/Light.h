#pragma once
#include "../Utilities/utilities.h"
enum MOVING {
	NONE,
	AXISX,AXISY,AXISZ,
	CIRCLEX
};
class Light {
public:
	int id;
	Vector3 color;
	Vector3 m_pos;
	Vector3 m_dir;
	void MakeMove(float);
	MOVING move;
	float speed;
	float radius;
};