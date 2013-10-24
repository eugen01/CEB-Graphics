precision mediump float;
uniform sampler2D u_texColor1;
varying vec2 v_uv;
void main()
{
	vec4 color = texture2D(u_texColor1, v_uv);
	float cl = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	gl_FragColor = vec4(cl, cl, cl, 1.0);
	
}
