#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class EBO {
public:
	GLuint ID;

	EBO(std::vector<int> data);

	void Bind();
	void Unbind();
	void Delete();
};

#endif