#include"EBO.h"

EBO::EBO(std::vector<GLuint> data) {
	for (size_t i = 0; i < data.size(); i += 3) {
		std::cout << data[i] << " " << data[i + 1] << " " << data[i + 2] << std::endl;
	}

	glGenBuffers(1, &ID);	//generating vbo object buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW); //look at vbo.cpp
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}
