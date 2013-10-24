#include <stdafx.h>
#include "Texture2D.h"
#include "../Utilities/memDbg.h"


Texture2D::Texture2D() {
	m_TexHandle = 0;
	m_wrapping = CLAMP_TO_EDGE;
}
Texture2D::~Texture2D(){
	if(m_TexHandle)
		glDeleteTextures(1,&m_TexHandle);
}
void Texture2D::Init2DTexture() 
{
	
	GLint w,h,bpp;
	char *buffer = LoadTGA(mfile,&w,&h,&bpp);
	glGenTextures(1,&m_TexHandle);
	glBindTexture(GL_TEXTURE_2D,m_TexHandle);
	
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	}
	else{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
	}
	if(m_wrapping == CLAMP_TO_EDGE) {
		
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	}
	if(m_wrapping == REPEAT) {
	
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}
	if(m_wrapping == MIRRORED_REPEAT) {
		
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
	}
	
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	 delete[] buffer;
}
