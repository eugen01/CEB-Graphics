precision mediump float;
varying vec3 v_posL;
uniform samplerCube s_TextureCube;
void main()
{
    gl_FragColor = textureCube(s_TextureCube, v_posL);
}
