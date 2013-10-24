attribute vec3 a_posL;
uniform mat4 u_wvp;
varying vec3 v_posL;
void main()
{
v_posL = -a_posL;
gl_Position = u_wvp*vec4(a_posL,1.0);
}