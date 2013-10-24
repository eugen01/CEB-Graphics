attribute vec3 a_posN;
attribute vec2 a_uv;
varying vec2 v_uv;
void main()
{
gl_Position = vec4(a_posN, 1.0);
v_uv = a_uv;
}