#version 150

uniform sampler2D usampler;

in vec2 vtexture_coord;
in float vtile_x;
in float vtile_y;
in vec4 vcolor;

out vec4 frag_color;

void main(void) {
	vec2 offsetCoords = vec2(vtexture_coord.x * vtile_x, vtexture_coord.y * vtile_y);
	frag_color = texture(usampler, offsetCoords) * vcolor;
}