#shader vertex
#version 410 core

layout(location = 0) in vec3 i_Position;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProj * u_Transform * vec4(i_Position, 1.0f);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
	o_Color = u_Color;
}