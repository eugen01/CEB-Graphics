precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texColor1;
uniform float u_Limit;
void main()
{
	vec4 color = texture2D(u_texColor1, v_uv);
	float cl = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	float val = step(u_Limit, cl);
	gl_FragColor = vec4(color.xyz * val,  color.a);

}