#ifndef COLLISION_CLASS_H
#define COLLISION_CLASS_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Camera.h"

class Collision {
	public:
		glm::vec3 disableX = glm::vec3(0, 1, 1);
		glm::vec3 disableY = glm::vec3(1, 1, 0);
		glm::vec3 allow = glm::vec3(1, 1, 1);

		float workOffset = 0.1f;		//yea it was catching other sides so it needs it

		glm::vec3 x_f;
		glm::vec3 x_b;
		glm::vec3 x_r;
		glm::vec3 x_l;
		glm::vec3 xx_f;
		glm::vec3 xx_b;
		glm::vec3 xx_r;
		glm::vec3 xx_l;
		glm::vec3 z_r;
		glm::vec3 z_l;
		glm::vec3 z_f;
		glm::vec3 z_b;
		glm::vec3 zz_r;
		glm::vec3 zz_l;
		glm::vec3 zz_f;
		glm::vec3 zz_b;
		glm::vec3 y;

		void Collisions(Camera& cameraObj, GLFWwindow* window, int(&world)[16][64][16]);
};

#endif