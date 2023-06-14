#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture;

void main()
{
  // Read the sprite's texture's color for the current pixel.
  vec4 textureColor = texture2D(u_texture, v_texCoord);
  
  // Tint the texture color by the sprite's color.
  gl_FragColor = v_fragmentColor*textureColor;
}
