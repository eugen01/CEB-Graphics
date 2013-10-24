#include <stdafx.h>
#include "TextureCube.h"
#include "../Utilities/memDbg.h"


TextureCube::TextureCube() {
	m_TexHandle = 0;

}
TextureCube::~TextureCube(){
	if(m_TexHandle)
		glDeleteTextures(1,&m_TexHandle);
}
void TextureCube::InitCubeTexture() 
{
	
	GLint w,h,bpp;
	char *buffer = LoadTGA(mfile,&w,&h,&bpp);
	glGenTextures(1,&m_TexHandle);
	glBindTexture(GL_TEXTURE_CUBE_MAP,m_TexHandle);
	char *face;
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	face = ExtractFace(w/4,w/4,buffer,w,bpp);
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	
	face = ExtractFace(w/4,0,buffer,w,bpp);
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	
	face = ExtractFace(0,w/4,buffer,w,bpp);
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	
	face = ExtractFace(w/4,w/2,buffer,w,bpp);
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	
	face = ExtractFace(w/2,w/4,buffer,w,bpp);
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	
	face = ExtractFace(3*w/4,w/4,buffer,w,bpp);
	
	if(bpp == 24) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,w/4,w/4,0,GL_RGB,GL_UNSIGNED_BYTE,face);
	}
	else{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGBA,w/4,w/4,0,GL_RGBA,GL_UNSIGNED_BYTE,face);
	}
	delete[] face;
	
	if(m_wrapping == CLAMP_TO_EDGE) {
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	}
	if(m_wrapping == REPEAT) {
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}
	if(m_wrapping == MIRRORED_REPEAT) {
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
		glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
	}
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ); 
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	delete[] buffer;
}

char* TextureCube::ExtractFace(int offx,int offy, char* buffer, int width,int bpp) {
	char *pStartRead;
	char *face;
	int dim = width * width * bpp / 128;
	face = new char[dim];
	pStartRead = buffer + (width * offy + offx) * bpp / 8;
	for(int i = 0 ; i < width / 4 ; i++) {
		memcpy_s(face + i * width * bpp / 32, dim, pStartRead, width * bpp / 32);
		pStartRead+=(width*bpp)/8;
	}
	return face;
}