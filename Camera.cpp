#include "Camera.h"
#include<cmath>

Camera::Camera(int width, int height, glm::vec3 position) {		//starting camera obejct
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::cameraSpeedApply(float speedD) {		//applying delta times
	timeDelta = speedD;

	velocity = pre_velocity * speedD / 9.81f;		//works 95%, there is a diffrence put it very small, 0.01 per *2 or /2 fps
	jump_speedAcce = pre_jump_speedAcce * speedD;	//works 100%
	sprintSpeed = pre_sprintSpeed * speedD;			//works 100%
	speed = pre_speed * speedD;						//works 100%

	//std::cout << jump_speedAcce << std::endl;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {		// camera settings
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);


	view = glm::lookAt(Position, Position + Orientation, Up);	//where from you look, where to look, up vector
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	cameraMatrix = projection * view;
	yaw = std::atan2(Orientation.z, Orientation.x);
	pitch = std::atan2(Orientation.y, std::sqrt(Orientation.x * Orientation.x + Orientation.z * Orientation.z));
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

bool Camera::Hitbox(float offset, glm::vec3 bMin, glm::vec3 bMax) {
	Cmin = glm::vec3(Position.x - CsizeHalf - offset, Position.y - Cheight - offset, Position.z - CsizeHalf - offset);
	Cmax = glm::vec3(Position.x + CsizeHalf + offset, Position.y + Cforhead + offset, Position.z + CsizeHalf + offset);

	if (Cmax.x < bMin.x || Cmin.x > bMax.x) {
		return false;
	}
	if (Cmax.y < bMin.y || Cmin.y > bMax.y) {
		return false;
	}
	if (Cmax.z < bMin.z || Cmin.z > bMax.z) {
		return false;
	}
	return true;
}

void Camera::Gravitation(bool work) {
	onGround = !work;

	if (work) {
		velocityDown += 9.81f *velocity;
		//Position.y -= (velocityDown * velocity)*9.81f;	//forspectator turn off
		//std::cout << velocityDown << std::endl;
	}
	else {
		velocityDown = velocity;
		//std::cout << "------------------" << std::endl;
	}
}

void Camera::Inputs(GLFWwindow* window, glm::vec3 frontCheck, glm::vec3 backCheck, glm::vec3 rightCheck, glm::vec3 leftCheck, glm::vec3 upCheck) {			//inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//Position.x += speedT * std::cos(yaw) * frontCheck.x;
		//Position.z += speedT * std::sin(yaw) * frontCheck.z;
		Position += speedT * Orientation;	//spectator
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position.x -= speedT * std::cos(yaw+glm::radians(90.0f)) * leftCheck.x;
		Position.z -= speedT * std::sin(yaw+glm::radians(90.0f)) * leftCheck.z;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position.x -= speedT * std::cos(yaw) * backCheck.x;
		Position.z -= speedT * std::sin(yaw) * backCheck.z;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position.x -= speedT * std::cos(yaw - glm::radians(90.0f)) * rightCheck.x;
		Position.z -= speedT * std::sin(yaw - glm::radians(90.0f)) * rightCheck.z;
	}

	if (((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS and onGround) or jumping) and upCheck.y) {
		if (time < 0) {
			time = glfwGetTime();
		}
		if (glfwGetTime() >= time + 0.1f and onGround) {
			jumpen = false;
			time = -1;
		}
		if (jump_speedUp > 0 and jumpen) {
			jump_speedUp -= jump_speedAcce;
			Position += jump_speedUp * Up * timeDelta;
			jumping = true;
		}
		else {
			jumpen = true;
			jumping = false;
			jump_speedUp = jump_speed;
		}
	}
	else {
		jumping = false;
		jump_speedUp = jump_speed;
	}
	

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Position += speedT * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		speedT = sprintSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
		speedT = speed;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS or inWindow) {
		inWindow = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotx = sesitivity * static_cast<float>(mouseY - (height / 2)) / height;
		float roty = sesitivity * static_cast<float>(mouseX - (width / 2)) / width;
		//rotx *= timeDelta;
		//roty *= timeDelta;
		//std::cout << rotx << " | " << roty << std::endl;
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, Up)));

		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation ;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-roty), Up);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
		inWindow = false;
	}
}
