uniform vec2 u_blurVector;

varying vec2 v_texCoord1;

uniform sampler2D u_texture;

void main(){
	const int nSamples = 8;
	
	vec4 result = texture2D(u_texture, v_texCoord1 + u_blurVector * -0.5);
	for (int i = 1; i < nSamples; ++i) {
		// get offset in range [-0.5, 0.5]:
		vec2 offset = u_blurVector * (float(i) / float(nSamples - 1) - 0.5);
	
		// sample & add to result:
		result += texture2D(u_texture, v_texCoord1 + offset);
	}
	
	result /= float(nSamples);
	
	gl_FragColor = result;
}