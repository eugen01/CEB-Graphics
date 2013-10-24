#include <stdafx.h>
#include "Objects.h"
#include "Globals.h"
#include "SM.h"
#include "../Utilities/memDbg.h"
void Object::ComputeWorldMatrix() {
	
	Matrix p;
	p.SetTranslation(m_pos);
	Matrix s;
	s.SetScale(m_scale);
	Matrix rx,ry,rz;
	rx.SetRotationX(m_rot.x);
	ry.SetRotationY(m_rot.y);
	rz.SetRotationZ(m_rot.z);
	m_world = s * rz * rx * ry * p;
	
}
void Object::Draw(Matrix view, Matrix perspective,float time,float dtime) {

	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_VertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_IndexBuffer);
	
	if(m_pShader->positionLoc != -1) {
	
		glEnableVertexAttribArray(m_pShader->positionLoc);
		glVertexAttribPointer(m_pShader->positionLoc, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), 0);
	}
	if(m_pShader->texCoordLoc != -1) {
	
		glEnableVertexAttribArray(m_pShader->texCoordLoc);
		glVertexAttribPointer (m_pShader->texCoordLoc,2, GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid *)(4*sizeof(Vector3)) );
		
	}
	if(m_pShader->sampler2DLoc != -1) {
	
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_p2DTextures[0]->m_TexHandle);
		glUniform1i ( m_pShader->sampler2DLoc, 0 );
	}
	if(m_pShader->matrixwvpLoc != -1) {
		ComputeWorldMatrix();
		glUniformMatrix4fv(m_pShader->matrixwvpLoc,1,GL_FALSE,(GLfloat*)&(m_world*view*perspective));
	}
	if(m_pShader->samplerCubeLoc != -1) {
		glActiveTexture ( GL_TEXTURE0 );
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_pCubeTextures[0]->m_TexHandle);
		glUniform1i ( m_pShader->samplerCubeLoc, 0);
	}
	if(m_pShader->normalMapLoc != -1) {
	
		glActiveTexture ( GL_TEXTURE1 );
		glBindTexture(GL_TEXTURE_2D, m_p2DTextures[0]->m_TexHandle);
		glUniform1i ( m_pShader->normalMapLoc, 1);
	}
	if(m_pShader->camLoc != -1) {
		Vector3 cam = SManager::GetInstance()->pCam->m_pos;
		glUniform3f(m_pShader->camLoc, cam.x,cam.y,cam.z); 
	}
	if(m_pShader->normalLoc != -1) {
		glEnableVertexAttribArray(m_pShader->normalLoc);
		glVertexAttribPointer (m_pShader->normalLoc,3, GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid *)(1*sizeof(Vector3)) );
	}
	if(m_pShader->tangentLoc != -1) {
		glEnableVertexAttribArray(m_pShader->tangentLoc);
		glVertexAttribPointer (m_pShader->tangentLoc,3, GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid *)(3*sizeof(Vector3)) );
	}
	if(m_pShader->binormLoc != -1) {
		glEnableVertexAttribArray(m_pShader->binormLoc);
		glVertexAttribPointer (m_pShader->binormLoc,3, GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid *)(2*sizeof(Vector3)) );
	}
	if(m_pShader->matrixwLoc != -1) {
		glUniformMatrix4fv(m_pShader->matrixwLoc,1,GL_FALSE,(GLfloat*)&(m_world));
	}
	if(m_pShader->tillingfactorLoc != -1) {
		glUniform1f(m_pShader->tillingfactorLoc, 0.5f);
	}
	if(m_pShader->sGrassLoc != -1) {
		glActiveTexture ( GL_TEXTURE1 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[0]->m_TexHandle);
		glUniform1i ( m_pShader->sGrassLoc, 1 );
	}
	if(m_pShader->sRockLoc != -1) {
		glActiveTexture ( GL_TEXTURE2 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[1]->m_TexHandle);
		glUniform1i (m_pShader->sRockLoc, 2 );
	}
	if(m_pShader->sDirtLoc != -1) {
		glActiveTexture ( GL_TEXTURE3 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[2]->m_TexHandle);
		glUniform1i ( m_pShader->sDirtLoc, 3 );
	}
	if(m_pShader->sBlendMapLoc != -1) {
		glActiveTexture ( GL_TEXTURE4 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[3]->m_TexHandle);
		glUniform1i ( m_pShader->sBlendMapLoc, 4 );
	}
	if(m_pShader->StartFogLoc != -1) {
		glUniform1f(m_pShader->StartFogLoc, 500);
	}
	if(m_pShader->RangeFogLoc != -1) {
		glUniform1f(m_pShader->RangeFogLoc, 2000);
	}
	if(m_pShader->FogColorLoc != -1) {
		glUniform3f(m_pShader->FogColorLoc,1,1,1);
	}
	if(m_pShader->dirlightLoc != -1) {
		Vector3 dir = SManager::GetInstance()->m_pLights[2].m_dir;
		glUniform3f(m_pShader->dirlightLoc,dir.x,dir.y,dir.z);
	}
	if(m_pShader->dirsourcecolorLoc != -1) {
		Vector3 color = SManager::GetInstance()->m_pLights[2].color;
		glUniform3f(m_pShader->dirsourcecolorLoc,color.x,color.y,color.z);
	}
	if(m_pShader->ambientalLoc != -1) {
		Vector3 color = SManager::GetInstance()->ambientcolor;
		glUniform3f(m_pShader->ambientalLoc,color.x,color.y,color.z);
	}
	if(m_pShader->blendingcountLoc != -1) {
		glUniform1f(m_pShader->blendingcountLoc,0.2f);
	}
	if(m_pShader->specularpowerLoc != -1) {
		glUniform1f(m_pShader->specularpowerLoc,50.0f);
	}
	if(m_pShader->pointlightpos1Loc != -1) {
		SManager::GetInstance()->m_pLights[0].MakeMove(dtime);
		Vector3 pos = SManager::GetInstance()->m_pLights[0].m_pos;
		glUniform3f(m_pShader->pointlightpos1Loc,pos.x,pos.y,pos.z);
	}
	if(m_pShader->pointlightcolor1Loc != -1) {
		Vector3 color = SManager::GetInstance()->m_pLights[0].color;
		glUniform3f(m_pShader->pointlightcolor1Loc,color.x,color.y,color.z);
	}
	if(m_pShader->pointlightpos2Loc != -1) {
		SManager::GetInstance()->m_pLights[1].MakeMove(dtime);
		Vector3 pos = SManager::GetInstance()->m_pLights[1].m_pos;
		glUniform3f(m_pShader->pointlightpos2Loc,pos.x,pos.y,pos.z);
	}
	if(m_pShader->pointlightcolor2Loc != -1) {
		Vector3 color = SManager::GetInstance()->m_pLights[1].color;
		glUniform3f(m_pShader->pointlightcolor2Loc,color.x,color.y,color.z);
	}
	if(m_pShader->sBottomWaterLoc != -1) {
		glActiveTexture ( GL_TEXTURE3 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[2]->m_TexHandle);
		glUniform1i (m_pShader->sBottomWaterLoc, 3 );
	}
	if(m_pShader->sDispMapLoc != -1) {
		glActiveTexture ( GL_TEXTURE2 );
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[1]->m_TexHandle);
		glUniform1i (m_pShader->sDispMapLoc, 2 );
	}
	if(m_pShader->sFireMaskLoc != -1) {
		glActiveTexture (GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D,m_p2DTextures[2]->m_TexHandle);
		glUniform1i (m_pShader->sFireMaskLoc, 3 );
	}
	if(m_pShader->timeLoc != -1) {
		glUniform1f (m_pShader->timeLoc, time);
	}
	if(id == 4 || id == 5) {
	
	glEnable ( GL_BLEND );
	
	glBlendFunc ( GL_SRC_ALPHA, GL_SRC_ALPHA );
	glBlendFunc ( GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	}
	
	glDrawElements(GL_TRIANGLES, m_pModel->m_nrIndici, GL_UNSIGNED_INT, 0);
	if(m_pShader->states[0] == 1) {
		glDisable(GL_BLEND);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D,0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}