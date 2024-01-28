#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class VBO {
public:
	GLuint ID;

	VBO(std::vector<glm::vec3> data);
	VBO(std::vector<glm::vec2> data);

	void Bind();
	void Unbind();
	void Delete();
};

#endif