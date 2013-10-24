precision mediump float;
varying vec3 v_dir;
uniform samplerCube s_TextureCube;
uniform sampler2D s_NormalMap;
uniform sampler2D s_Bottom;
uniform sampler2D u_dispmap;
uniform float u_time;
uniform vec3 u_camw;

varying vec3 v_normW;
varying vec3 v_tanW;
varying vec3 v_binormW;

varying vec3 v_posW;
varying vec3 v_toeye;
varying vec2 v_texCoord;
void main()
{
	//up
		
	vec2 disp = texture2D(u_dispmap,vec2(v_texCoord.x,v_texCoord.y+u_time/10.0)).xy;
	vec2 newuv = v_texCoord + (2.0*disp - 1.0)*1.0;
	mat3 TBN = mat3(normalize(v_tanW),normalize(v_binormW),normalize(v_normW));
	vec3 normT = normalize(2.0 * texture2D(s_NormalMap,newuv).xyz-1.0);
	vec3 normW = normalize(TBN * normT);
	
	vec3 toeye = normalize(u_camw - v_posW);
	vec3 v_dir = normalize(reflect(-toeye,normW));
	vec4 coloru = textureCube(s_TextureCube,v_dir);
	
	//bootom
	float dRefraction = v_texCoord.x * 0.05;
	vec2 newuv2 = v_texCoord + dRefraction * (2.0 * disp-1.0);
	float factadancime = clamp(v_texCoord.x,0.0,1.0);
	vec4 colorwater = vec4(0.0,0.0,1.0,1.0);
	vec4 colorb = mix(texture2D(s_Bottom,newuv2),colorwater,factadancime);

	//fresnel
	float f = 1.0 - abs(dot(normW,toeye));
	gl_FragColor = colorb * (1.0-f) + coloru * (f);
    
}