precision mediump float;
varying vec4 v_vposw;
varying vec2 v_uvo;
varying vec2 v_uvt;
uniform sampler2D u_sGrass,u_sRock,u_sDirt,u_sBlendMap;
uniform vec3 u_camw;
uniform float u_fStartFog;
uniform float u_fRangeFog;
uniform vec3 u_vFogColor;
void main()
 {
vec4 vgrasscolor = texture2D(u_sGrass,v_uvt);
vec4 vrockcolor = texture2D(u_sRock,v_uvt);
vec4 vdirtcolor = texture2D(u_sDirt,v_uvt);
vec3 vblend = (texture2D(u_sBlendMap, v_uvo)).rgb;
vec4 vBaseColor = (vgrasscolor*(vblend.r) + vdirtcolor*(vblend.g) + vrockcolor*(vblend.b))/(vblend.r+vblend.g+vblend.b);
float Dist = distance(u_camw,v_vposw.xyz);
float FogFact = clamp((Dist - u_fStartFog)/u_fRangeFog,0.0,1.0);
gl_FragColor = vec4(mix(vBaseColor.rgb,u_vFogColor,FogFact),vBaseColor.a);
}