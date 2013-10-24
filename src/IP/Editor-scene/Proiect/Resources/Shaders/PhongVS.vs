attribute vec3 a_posL;
attribute vec3 a_normL;
uniform mat4 u_wvp;
uniform mat4 u_w;
attribute vec2 a_texCoord;
varying vec3 v_posW;
varying vec3 v_normW;
varying vec2 v_texCoord;
void main() {

v_texCoord = a_texCoord; 
v_posW = (u_wvp * vec4(a_posL,1.0)).xyz;
v_normW = (normalize(u_w * vec4(a_normL,0.0))).xyz;
gl_Position = u_wvp * vec4(a_posL,1.0);

}