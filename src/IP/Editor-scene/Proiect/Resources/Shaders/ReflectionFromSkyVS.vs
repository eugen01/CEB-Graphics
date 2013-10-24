attribute vec3 a_posL;
attribute vec3 a_normL;
uniform mat4 u_wvp;
uniform vec3 u_camw;
uniform mat4 u_w;
varying vec3 v_dir;

void main()
{
vec3 toeye = normalize(u_camw - (u_w*vec4(a_posL,1.0)).xyz);
v_dir = normalize(reflect(-toeye,normalize(u_w*vec4(a_normL,0.0)).xyz));
gl_Position = u_wvp*vec4(a_posL,1.0);
}