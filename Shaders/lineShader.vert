#version 150
in vec4 position;

uniform mat4 cam_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform vec4 color;

out vec4 vcolor;

void main() {
	gl_Position = cam_matrix * view_matrix * model_matrix * position;
	vcolor = color;
}