uniform vec2 u_noiseTextureSize;
uniform vec2 u_viewSizeInPixels;

attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying mediump vec4 v_fragmentColor;
varying mediump vec2 v_texCoord1;
varying mediump vec2 v_texCoord2;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
#endif

uniform mat4 u_MVPMatrix;
uniform vec4 u_time;

void main(){
    gl_Position = u_MVPMatrix * a_position;
	v_fragmentColor = clamp(a_color, 0.0, 1.0);
	v_texCoord1 = a_texCoord;
	
    vec2 distortionScroll = vec2(u_time[1], 0.0);
    vec2 screen_0_to_1 = (0.5 * gl_Position.xy / gl_Position.w + 0.5);
	v_texCoord2 = screen_0_to_1 * u_viewSizeInPixels / u_noiseTextureSize + distortionScroll;

    //v_texCoord2 = gl_Position.xy / gl_Position.w + distortionScroll;
}