#version 130
in vec4 position;
in vec2 texture_coord;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

out vec4 vcolor;
out vec2 vtexture_coord;

void main() {
	vec4 P = model_matrix * position;
	gl_Position = P;
	vtexture_coord = texture_coord;
}