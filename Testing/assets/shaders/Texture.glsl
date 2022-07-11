#type vertex
#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 vTexCoord;

void main()
{
	vTexCoord = inTexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
}


#type fragment
#version 450

layout(location = 0) out vec4 outColor;

in vec2 vTexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	outColor = texture(u_Texture, vTexCoord * 10.0) * u_Color;
}
