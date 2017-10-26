#version 130

uniform sampler2D usampler;

in vec2 vtexture_coord;

out vec4 frag_color;

void main(void) {
	vec3 diffuse_color = texture(usampler, vtexture_coord).xyz;
	frag_color = vec4(diffuse_color, 1);
}