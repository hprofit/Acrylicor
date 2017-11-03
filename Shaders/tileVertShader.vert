#version 150
in vec4 position;
in vec2 texture_coord;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;
uniform float tile_x;
uniform float tile_y;
uniform vec4 color;

out vec4 vcolor;
out vec2 vtexture_coord;
out float vtile_x;
out float vtile_y;

void main() {
	vec4 P = model_matrix * position;
	gl_Position = persp_matrix * view_matrix * P;
	vtexture_coord = texture_coord;
	vtile_x = tile_x;
	vtile_y = tile_y;
	vcolor = color;
}