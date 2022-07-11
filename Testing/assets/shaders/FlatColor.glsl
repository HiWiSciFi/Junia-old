#type vertex
#version 450

layout(location = 0) in vec3 inPosition;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
}


#type fragment
#version 450

layout(location = 0) out vec4 outColor;

uniform vec4 u_Color;

void main()
{
	outColor = u_Color;
}
