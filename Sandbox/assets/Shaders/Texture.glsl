#shader vertex
#version 430 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;
layout(location = 2) in vec2 i_TexCoord;
layout(location = 3) in float i_TexIndex;
layout(location = 4) in float i_TilingFactor;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;

uniform mat4 u_ViewProj;

void main()
{
	v_Color = i_Color;
	v_TexCoord = i_TexCoord;
	v_TexIndex = i_TexIndex;
	v_TilingFactor = i_TilingFactor;
	gl_Position = u_ViewProj * vec4(i_Position, 1.0);
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
	o_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
}