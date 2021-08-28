#shader vertex
#version 410 core

layout(location = 0) in vec3 i_Position;

void main()
{
	gl_Position = vec4(i_Position, 1.0f);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 o_Color;

void main()
{
	o_Color = vec4(0.2f, 0.8f, 0.3f, 1.0f);
}