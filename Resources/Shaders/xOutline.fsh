#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_outlineColor;
uniform float u_outlineWidth;

uniform sampler2D u_texture;

vec4 composite(vec4 over, vec4 under){
    return over + (1.0 - over.a)*under;
}

void main(){
    float width = u_outlineWidth;
    float outlineAlpha = 0.0;

    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(width, 0.0)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(-width, 0.0)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(0.0, width)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(0.0, -width)).a;
    
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(width, width)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(-width, width)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(width, -width)).a;
    outlineAlpha += texture2D(u_texture, v_texCoord + vec2(-width, -width)).a;
    
    vec4 outlineColor = u_outlineColor * outlineAlpha;
    vec4 textureColor = texture2D(u_texture, v_texCoord);
    gl_FragColor = composite(textureColor, outlineColor);
}
