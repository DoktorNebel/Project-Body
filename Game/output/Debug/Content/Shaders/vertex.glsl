#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in mat4 model;
layout(location = 5) in vec2 uv[4];

uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main()
{
	mat4 mvp = view * projection * model;
    gl_Position = mvp * vec4(position, 1.0);
	texCoord = uv[gl_VertexID];
}