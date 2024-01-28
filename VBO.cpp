#include"VBO.h"
#include <iostream>

VBO::VBO(std::vector <glm::vec3> data) {
	glGenBuffers(1, &ID);	//generating vbo object buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	//this might not work, im using .data() as a replacement of .ToArray from c# and im not sure what is the result
	Unbind();
}
VBO::VBO(std::vector <glm::vec2> data) {
	glGenBuffers(1, &ID);	//generating vbo object buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);	//this might not work, im using .data() as a replacement of .ToArray from c# and im not sure what is the result
	Unbind();
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}