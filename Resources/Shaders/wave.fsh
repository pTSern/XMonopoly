varying vec2 v_texCoord;

uniform vec3 u_random;
uniform sampler2D u_texture;

vec2 SineWave(vec2 p) 
{
    float x;
    x = 0.03 * sin( 25.0 * p.y + u_random.x * 5.0 );
    return vec2(p.x+x, p.y);
}

void main() {
    gl_FragColor = texture2D(u_texture, SineWave(v_texCoord));
}
