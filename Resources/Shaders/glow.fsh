varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

uniform float u_ctime;
uniform float u_gtime;
uniform float u_radius;
uniform vec4 u_color;

uniform sampler2D u_texture;

void main()
{
    float radius = u_radius;
    
    vec4 accum = vec4(0.0);
    vec4 normal = vec4(0.0);
    
    normal = texture2D(u_texture, v_texCoord);
    
    for(float i = 1.0; i <= radius; i += 1.0)
    {
        accum += texture2D(u_texture, vec2(v_texCoord.x - 0.01 * i, v_texCoord.y - 0.01 * i));
        accum += texture2D(u_texture, vec2(v_texCoord.x + 0.01 * i, v_texCoord.y - 0.01 * i));
        accum += texture2D(u_texture, vec2(v_texCoord.x + 0.01 * i, v_texCoord.y + 0.01 * i));
        accum += texture2D(u_texture, vec2(v_texCoord.x - 0.01 * i, v_texCoord.y + 0.01 * i));
    }


    //accum.rgb =  u_color.rgb * u_color.a * accum.a * 0.95;
	
	accum.rgb =  u_color.rgb * u_color.a * accum.a;
	
    float opacity = ((1.0 - normal.a) / radius) * (sin(u_ctime)/5.0 / u_gtime);
    
    normal = (accum * opacity) + (normal * normal.a);
    
    gl_FragColor = v_fragmentColor * normal;
}
