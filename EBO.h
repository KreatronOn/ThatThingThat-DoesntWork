#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<iostream>	//delete after ending debugging

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

	EBO(std::vector<GLuint> data);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
