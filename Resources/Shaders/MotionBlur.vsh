uniform vec2 u_noiseTexturePixelSize;
uniform vec2 u_viewSizeInPixels;

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying mediump vec2 v_texCoord1;
#else
varying vec2 v_texCoord1;
#endif

uniform mat4 u_MVPMatrix;
uniform vec4 u_Random01;

void main()
{
	gl_Position = u_MVPMatrix * a_position;
//	cc_FragColor = clamp(a_color, 0.0, 1.0);
	v_texCoord1 = a_texCoord;

//	vec2 uv = (0.5 * gl_Position.xy/ gl_Position.w + 0.5 + u_Random01.xy);
//	cc_FragTexCoord2 = uv * u_viewSizeInPixels / u_noiseTexturePixelSize;
}