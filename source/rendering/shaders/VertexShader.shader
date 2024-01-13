#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 vertexColour;

layout(location = 0) out vec4 colour;

void main()
{
	gl_Position = vec4((position.x / 1000) - 1, (position.y / 1000) - 1, 0.0, 1.0);
	colour = vec4(vertexColour, 1.0);
}