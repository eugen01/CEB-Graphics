attribute vec3 a_posL;
attribute vec3 a_normL;
attribute vec3 a_tanL;
attribute vec3 a_binormL;
attribute vec2 a_texCoord;

uniform mat4 u_wvp;
uniform mat4 u_w;

varying vec2 v_texCoord;
varying vec3 v_normW;
varying vec3 v_tanW;
varying vec3 v_binormW;
varying vec3 v_posW;
void main()
{
v_posW = (u_w * vec4(a_posL,1.0)).xyz;
v_texCoord = a_texCoord;
v_normW = normalize(u_w * vec4(a_normL,0.0)).xyz;
v_tanW = normalize(u_w * vec4(a_tanL,0.0)).xyz;
v_binormW = normalize(u_w * vec4(a_binormL,0.0)).xyz;
gl_Position = u_wvp*vec4(a_posL,1.0);
}