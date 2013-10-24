precision mediump float;
varying vec3 v_dir;
uniform samplerCube s_TextureCube;
void main()
{
    gl_FragColor = textureCube(s_TextureCube, -v_dir);
}
