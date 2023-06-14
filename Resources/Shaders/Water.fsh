uniform sampler2D u_noiseTexture;
uniform sampler2D u_causticTexture;

#ifdef GL_ES
varying mediump vec4 v_fragmentColor;
varying mediump vec2 v_texCoord1;
varying mediump vec2 v_texCoord2;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
#endif

uniform sampler2D u_texture;

void main(){
	vec2 distortion = 2.0 * texture2D(u_noiseTexture, v_texCoord2).xy - 1.0;
	vec2 distortionOffset = distortion * 0.15;
    gl_FragColor =  texture2D(u_texture, v_texCoord1 + distortionOffset);
	gl_FragColor += 0.5 * texture2D(u_causticTexture, v_texCoord1 - distortionOffset);
}