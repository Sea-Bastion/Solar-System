#version 440

//in vars
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;

//uniform vars
layout (location = 2) uniform vec3 translate;
layout (location = 3) uniform mat3 rotate;
layout (location = 4) uniform mat3 scale;
layout (location = 5) uniform vec2 size;

//out vars
out vec3 vs_position;
out vec2 vs_texcoord;

//other vars
vec3 trans_position;

void main()
{
	vs_position = vertex_position;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);

	
	trans_position = rotate * scale * vertex_position + translate;
	gl_Position =  vec4(trans_position.x/size.x, trans_position.y/size.y, trans_position.z, 1.f);
	//gl_Position = vec4(trans_position, 1.f);
}