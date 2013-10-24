attribute vec3 a_posL;
attribute vec2 a_texCoord;
varying vec2 v_texCoord; 
uniform mat4 u_wvp;
void main()
{
v_texCoord = a_texCoord;
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_wvp * posL;
}
 