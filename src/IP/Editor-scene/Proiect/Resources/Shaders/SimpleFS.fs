precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_Texture2D;
void main()
{
	gl_FragColor = texture2D( s_Texture2D, v_texCoord );
}