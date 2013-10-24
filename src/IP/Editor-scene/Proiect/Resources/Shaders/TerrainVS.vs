attribute vec3 a_posL;
uniform mat4 u_wvp;
uniform mat4 u_w;
varying vec4 v_vposw;
attribute vec2 a_texCoord;
varying vec2 v_uvo;
varying vec2 v_uvt;
uniform float u_fTillingFactor;
void main()
{
	v_vposw = u_w * vec4(a_posL,1.0);
	v_uvo = a_texCoord;
	v_uvt = a_texCoord * u_fTillingFactor;
	gl_Position = u_wvp * vec4(a_posL,1.0);
}