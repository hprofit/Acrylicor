#version 130

uniform sampler2D usampler;

in vec2 vtexture_coord;

out vec4 frag_color;

void main(void) {
	frag_color = texture(usampler, vtexture_coord);
}