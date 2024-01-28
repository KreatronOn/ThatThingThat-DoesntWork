#ifndef PLACING_CLASS_H
#define PLACING_CLASS_H

#include"Camera.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Placing {
	public:
		float Dnow;
		float Dthen = 4;
		int xHit = 0;
		int yHit = 0;
		int zHit = 0;

		bool clickL = true;
		int clickR = true;

		float collisionPoint;
		glm::vec3 collisionLocation;

		float yaw;
		float pitch;

		int collisionX;
		int collisionY;
		int collisionZ;

		void LookAtBlock(glm::vec3 minPoint, Camera& camera);

		void Click(int (&world)[16][64][16], GLFWwindow* window, Camera& camera);
};

#endif