#version 440

//in vars
layout (location = 0) in vec3 vertex_position;
//layout (location = 1) in vec3 vertex_color;
layout (location = 1) in vec2 vertex_texcoord;

//uniform vars
layout (location = 2) uniform vec4 translate;
layout (location = 3) uniform mat4 rotate;
layout (location = 4) uniform vec2 screen_size;

//out vars
out vec3 vs_position;
//out vec3 vs_color;
out vec2 vs_texcoord;

//other vars
vec3 rel_position;

void main()
{
	vs_position = vertex_position;
//	vs_color = vertex_color;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);

	rel_position = vec3(vertex_position.x/screen_size.x, vertex_position.y/screen_size.y, vertex_position.z);

	//gl_Position = rotate * vec4(rel_position, 1.f) + translate;
	gl_Position = vec4(rel_position, 1.f);
}