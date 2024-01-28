#include"Placing.h"

bool rayIntersection(glm::vec3 minPoint, Camera& camera, float& tmin) {
	glm::vec3 rayOrigin = camera.Position;
	glm::vec3 rayDirection = camera.Orientation;
	glm::vec3 maxPoint = minPoint + glm::vec3(1, 1, 1);
	float t1 = (minPoint.x - rayOrigin.x) / rayDirection.x;
	float t2 = (maxPoint.x - rayOrigin.x) / rayDirection.x;
	float t3 = (minPoint.y - rayOrigin.y) / rayDirection.y;
	float t4 = (maxPoint.y - rayOrigin.y) / rayDirection.y;
	float t5 = (minPoint.z - rayOrigin.z) / rayDirection.z;
	float t6 = (maxPoint.z - rayOrigin.z) / rayDirection.z;

	tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
	float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

	return tmax >= tmin && tmax >= 0.0f;
}

void Placing::LookAtBlock(glm::vec3 minPoint, Camera& camera) {
	glm::vec3 myPos = glm::vec3(int(floor(camera.Position.x)), int(floor(camera.Position.y)), int(floor(camera.Position.z)));

	Dnow = glm::distance(myPos, minPoint);

	if (rayIntersection(minPoint, camera, collisionPoint)) {
		if (Dnow <= Dthen) {
			xHit = minPoint.x;
			yHit = minPoint.y;
			zHit = minPoint.z;
			Dthen = Dnow;
		}

	}
	yaw = camera.yaw;
	pitch = camera.pitch;
}

void Placing::Click(int (&world)[16][64][16], GLFWwindow* window, Camera& camera) {
	if (rayIntersection(glm::vec3(xHit, yHit, zHit), camera, collisionPoint)) {
		if (Dthen <= 4) {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS and clickL) {
				clickL = false;
				world[xHit][yHit][zHit] = 0;
			}
			else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
				clickL = true;
			}

			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS and clickR) {
				collisionLocation = camera.Position + collisionPoint * camera.Orientation;
				if (yaw < 1.5708f && yaw > -1.5708f) {
					collisionX = floor(collisionLocation.x - 0.00001f);
				}
				else {
					collisionX = floor(collisionLocation.x);
				}
				if (pitch < 0) {
					collisionY = floor(collisionLocation.y);
				}
				else {
					collisionY = floor(collisionLocation.y - 0.00001f);
				}

				if (yaw < 0) {
					collisionZ = floor(collisionLocation.z);
				}
				else {
					collisionZ = floor(collisionLocation.z - 0.00001f);
				}
				if (collisionX != xHit and !camera.Hitbox(0.0f, glm::vec3(collisionX, collisionY, collisionZ), glm::vec3(collisionX+1, collisionY+1, collisionZ+1))) {
					world[collisionX][yHit][zHit] = 1;
				}
				if (collisionY != yHit and !camera.Hitbox(0.0f, glm::vec3(collisionX, collisionY, collisionZ), glm::vec3(collisionX + 1, collisionY + 1, collisionZ + 1))) {
					world[xHit][collisionY][zHit] = 1;
				}
				if (collisionZ != zHit and !camera.Hitbox(0.0f, glm::vec3(collisionX, collisionY, collisionZ), glm::vec3(collisionX + 1, collisionY + 1, collisionZ + 1))) {
					world[xHit][yHit][collisionZ] = 1;
				}
				clickR = false;
			}
			else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
				clickR = true;
			}
			//std::cout << "look at block: " << xHit << " | " << yHit << " | " << zHit << "			collision: " << collisionLocation.x << " | " << collisionLocation.y << " | " << collisionLocation.z << "			new block: " << collisionX << " | " << collisionY << " | " << collisionZ << "     my pos: " << int(floor(camera.Position.x)) << " | " << int(floor(camera.Position.y)) << " | " << int(floor(camera.Position.z)) << std::endl;
		}
	}
	Dthen = 10;
}