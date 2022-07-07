#type vertex
#version 450

layout(location = 0) in vec3 inPosition;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 vPosition;

void main()
{
	vPosition = inPosition;
	gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
}


#type fragment
#version 450

layout(location = 0) out vec4 outColor;

in vec3 vPosition;

uniform vec3 u_Color;

void main()
{
	outColor = vec4(u_Color, 1.0f);
}
