#include"VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VAO::LinkAttrib(int location, int size, VBO& VBO) {
	Bind();
	VBO.Bind();

	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);

	Unbind();
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}