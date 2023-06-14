attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;


#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform mat4 u_MVPMatrix;

void main(){
    gl_Position = u_MVPMatrix * a_position;
    v_fragmentColor = clamp(a_color, 0.0, 1.0);
    v_texCoord = a_texCoord;
}

