#version 330 core
layout (location = 0) in vec3 aPosition; // vertex coordinates
//layout (location = 1) in vec2 aTexCoord; // texture coordinates

//out vec2 texCoord;

// uniform variables
uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 camMatrix;

void main() 
{
	gl_Position =  camMatrix * model * vec4(aPosition, 1.0); // coordinates
	//texCoord = aTexCoord;
}e