#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"
#include"Speed.h"

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	glm::mat4 view;
	glm::mat4 projection;

	bool firstClick = true;

	int width;
	int height;

	float yaw;
	float pitch;

	float Cheight = 1.6f;
	float Cforhead = 0.1f;
	float CsizeHalf = 0.25f;
	glm::vec3 Cmin;
	glm::vec3 Cmax;

	bool jumping = false;
	bool jump = false;
	bool onGround = true;

	bool inWindow = false;
	
	bool canJump = true;
	bool jumpen = true;
	float time = -1;

	float timeDelta;

	float velocityDown = 0.05f;			//has to have
	float jump_speedUp = 0.01f;
	float jump_speed = 8.5f;
	float sesitivity = 25.0f;
	float velocity;						//speeds with apllied delta times (nothing here should have value)
	float sprintSpeed;
	float speed;
	float speedT;
	float jump_speedAcce;
	
	float pre_velocity = 3.5f; /** 0.0069444f *0.0069444f;	*/	//base speeds, without delta times
	float pre_speed =3.5f;
	float pre_sprintSpeed =7.0f;
	float pre_jump_speedAcce = 15.0f;

	Camera(int width, int height, glm::vec3 position);

	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window, glm::vec3 frontCheck, glm::vec3 backCheck, glm::vec3 rightCheck, glm::vec3 leftCheck, glm::vec3 upCheck);

	void cameraSpeedApply(float speed);

	void Gravitation(bool work);

	bool Hitbox(float offset, glm::vec3 bMin, glm::vec3 bMax);
};

#endif
