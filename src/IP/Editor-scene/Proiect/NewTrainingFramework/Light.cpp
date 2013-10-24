#include <stdafx.h>
#include "../Utilities/memDbg.h"
#include "Light.h"
#include <cmath>

void Light::MakeMove(float deltaTime) {
	Matrix p;
	switch(move) {
		case NONE:
			
			break;
		case AXISX:
			m_pos.x += speed*deltaTime;
			
			if(m_pos.x > radius || m_pos.x < -radius)
				speed*=(-1);
			
			break;
		case AXISY:
			
			m_pos.y += speed*deltaTime;
			
			if(m_pos.y > radius || m_pos.y < -radius)
				speed*=(-1);
			
			break;
		case AXISZ:
			
			m_pos.z += speed*deltaTime;
			
			if(m_pos.y > radius || m_pos.y < -radius)
				speed*=(-1);
			
			break;
		case CIRCLEX:
		
			p.SetRotationX(speed*deltaTime);
			Vector4 m_poss = p * Vector4(m_pos.x,m_pos.y,m_pos.z,1.0); 
			m_pos = Vector3(m_poss.x,m_poss.y,m_poss.z);

			break;
	
	
	}
}