precision mediump float;
varying vec3 v_posW;
varying vec3 v_normW;
varying vec2 v_texCoord;
uniform sampler2D s_Texture2D;
uniform vec3 u_dirlight;
uniform vec3 u_camw;
uniform vec3 u_dirsourcecolor;
uniform float u_specularpower;
uniform vec3 u_ambiental;
uniform float blendingcount;

uniform vec3 u_pointsourcecolor1;
uniform vec3 u_pointcolor1;

uniform vec3 u_pointsourcecolor2;
uniform vec3 u_pointcolor2;

void main() {
	//directional
	vec3 v_diffuse = max(0.0,dot(-u_dirlight,v_normW)) * u_dirsourcecolor;
	vec3 reflec = normalize(reflect(u_dirlight,normalize(v_normW)));
	vec3 toeye = normalize(u_camw-v_posW);
	vec3 v_spec = pow(max(0.0,dot(reflec,toeye)),u_specularpower) * u_dirsourcecolor;
	//point1
	vec3 v_dirlight1 = normalize(v_posW - u_pointsourcecolor1);
	vec3 v_diffuse1 = max(0.0,dot(-v_dirlight1,v_normW)) * u_pointcolor1;
	vec3 reflec1 = normalize(reflect(v_dirlight1,v_normW));
	vec3 v_spec1 = pow(max(0.0,dot(reflec1,toeye)),u_specularpower) * u_pointcolor1;
	//point2
	vec3 v_dirlight2 = normalize(v_posW - u_pointsourcecolor2);
	vec3 v_diffuse2 = max(0.0,dot(-v_dirlight2,v_normW)) * u_pointcolor2;
	vec3 reflec2 = normalize(reflect(v_dirlight2,v_normW));
	vec3 v_spec2 = pow(max(0.0,dot(reflec2,toeye)),u_specularpower) * u_pointcolor2;
	
	gl_FragColor = vec4((blendingcount * u_ambiental + (1.0-blendingcount) * (v_diffuse + v_diffuse1 + v_diffuse2 ))*(texture2D(s_Texture2D,v_texCoord).xyz) + v_spec + v_spec1 + v_spec2,1.0);

}