attribute vec3 a_posL;
attribute vec2 a_texCoord;
varying vec2 v_uv;
uniform mat4 u_wvp;
void main()
{
v_uv = a_texCoord;
gl_Position = u_wvp * vec4(a_posL,1.0);
}
   