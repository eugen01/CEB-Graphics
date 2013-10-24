precision mediump float;
varying vec2 v_uv;
uniform sampler2D s_Texture2D;
uniform sampler2D u_dispmap;
uniform sampler2D u_firemask;
uniform float u_time;
void main()
{
vec2 disp = texture2D(u_dispmap,vec2(v_uv.x,v_uv.y+u_time)).xy;
vec2 newuv = v_uv + (2.0*disp - 1.0)*0.2;
vec4 color = texture2D(s_Texture2D,newuv);
vec4 alphamask = texture2D(u_firemask,v_uv);
gl_FragColor = color * vec4(1.0,1.0,1.0,alphamask.a);
}