#shader vertex
#version 410 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TexCoord;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = i_TexCoord;
	gl_Position = u_ViewProj * u_Transform * vec4(i_Position, 1.0f);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Texture;
uniform float u_TileCount = 1.0f;

in vec2 v_TexCoord;

void main()
{
	o_Color = texture(u_Texture, v_TexCoord * u_TileCount);
}