precision mediump float;
uniform sampler2D u_texColor1;
uniform sampler2D u_texColor2;
varying vec2 v_uv;
void main()
{
	gl_FragColor = texture2D(u_texColor1, v_uv) + texture2D(u_texColor2, v_uv);
}