#include <stdafx.h>
#include <iostream>
#include "Model.h"
#include "Shaders.h"
#include "Vertex.h"
#include "Camera.h"
#include "../Utilities/memDbg.h"
Matrix m;
float rottt=0;
Model::Model() {
	m_IndexBuffer = 0;
	m_VertexBuffer = 0;

}

Model::~Model() {
	if(m_VertexBuffer)
		glDeleteBuffers(1,&m_VertexBuffer);
	if(m_IndexBuffer)
		glDeleteBuffers(1,&m_IndexBuffer);
}

void Model::LoadModel() 
{

	FILE *f;
	int nr=4;
	float px,py,pz,nx,ny,nz,bx,by,bz,tx,ty,tz,u,v;
	Vertex *vector;
	GLuint *indici;
	GLint indice;
	char junk[200],junk2[7]; 
	errno_t err = fopen_s(&f,mfile,"r");
	m.SetIdentity();
	if(err)
		printf_s("nu s-a deschis\n");
	else {
		fscanf_s(f,"%s",junk,200);
		fscanf_s(f,"%d",&m_nrVertex);
		vector = new Vertex[m_nrVertex];

		for(int i = 0 ; i < m_nrVertex; i++) {
			
			fscanf_s( f, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&px, &py, &pz, &nx, &ny, &nz, &bx, &by, &bz, &tx, &ty, &tz, &u, &v );

			vector[i].pos.x = px; vector[i].pos.y = py; vector[i].pos.z = pz;
			vector[i].norm.x = nx; vector[i].norm.y = ny; vector[i].norm.z = nz;
			vector[i].binorm.x = bx; vector[i].binorm.y = by; vector[i].binorm.z = bz; 
			vector[i].tangent.x = tx; vector[i].tangent.y = ty; vector[i].tangent.z = tz;
			vector[i].uv.x = u; vector[i].uv.y = v;
			
		}
		fscanf_s(f,"%s",junk,200);
		fscanf_s(f,"%d",&m_nrIndici);
		indici = new GLuint[m_nrIndici];
		for(int i =0 ; i < m_nrIndici / 3; i++) {
			fscanf_s(f,"%d", &indice);
			fscanf_s(f,"%1c%u%1c%u%1c%u",junk2,7, &indici[3*i],junk2,7,&indici[3*i+1],junk2,7,&indici[3*i+2]);
		}
	}
	fclose(f);

	glGenBuffers(1,&m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nrVertex*sizeof(Vertex), vector, GL_STATIC_DRAW);

	glGenBuffers(1,&m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nrIndici*sizeof(GLuint), indici, GL_STATIC_DRAW);
	delete[] indici;
	delete[] vector;

}
