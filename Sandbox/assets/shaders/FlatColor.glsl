#type vertex
#version 330 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_TexCoord;

uniform mat4 VPMat;
uniform mat4 u_ModelMatrix;
			
void main()
{
	gl_Position = VPMat* u_ModelMatrix * vec4(a_Position,1.0);
}

#type fragment
#version 330 core
			
layout(location=0) out vec4 color;

uniform vec4 u_Color;

void main() 
{ 
	color = u_Color;
}