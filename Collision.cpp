#include"Collision.h"

void Collision::Collisions(Camera& camera, GLFWwindow* window, int(&world)[16][64][16]) {
	camera.Cmin = glm::vec3(camera.Position.x - camera.CsizeHalf, camera.Position.y - camera.Cheight, camera.Position.z - camera.CsizeHalf);
	camera.Cmax = glm::vec3(camera.Position.x + camera.CsizeHalf, camera.Position.y + camera.Cforhead, camera.Position.z + camera.CsizeHalf);

	camera.Cmin.y -= workOffset + 0.1f;
	if (world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))]) {
		camera.Gravitation(false);
	}
	else {
		camera.Gravitation(true);
	}
	camera.Cmin.y += workOffset + 0.1f;

	x_f = allow;
	x_b = allow;
	x_r = allow;
	x_l = allow;
	xx_f = allow;
	xx_b = allow;
	xx_r = allow;
	xx_l = allow;
	z_r = allow;
	z_l = allow;
	z_f = allow;
	z_b = allow;
	zz_r = allow;
	zz_l = allow;
	zz_f = allow;
	zz_b = allow;
	y = allow;

	camera.Cmax.x += workOffset;
	if (world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))]) {
		if (camera.yaw < 1.5708f && camera.yaw > -1.5708f) {
			//std::cout << "f+" << "  ";
			x_f = disableX;
			if (camera.yaw > 0) {
				x_l = disableX;
			}
			else {
				x_r = disableX;
			}
		}
		else {
			//std::cout << "f-" << "  ";
			x_b = disableX;
			if (camera.yaw > 0) {
				x_l = disableX;
			}
			else {
				x_r = disableX;
			}
		}
	}
	camera.Cmax.x -= workOffset;
	camera.Cmin.x -= workOffset;
	if (world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))]) {
		if (camera.yaw < 1.5708f && camera.yaw > -1.5708f) {
			//std::cout << "b+" << "  ";
			xx_b = disableX;
			if (camera.yaw > 0) {
				xx_r = disableX;
			}
			else {
				xx_l = disableX;
			}
		}
		else {
			//std::cout << "b-" << "  ";
			xx_f = disableX;
			if (camera.yaw > 0) {
				xx_r = disableX;
			}
			else {
				xx_l = disableX;
			}
		}
	}
	camera.Cmin.x += workOffset;
	camera.Cmax.z += workOffset;
	if (world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmax.z))]) {
		if (camera.yaw < 1.5708f && camera.yaw > -1.5708f) {
			//std::cout << "r+" << "  ";
			z_r = disableY;
			if (camera.yaw > 0) {
				z_f = disableY;
			}
			else {
				z_b = disableY;
			}
		}
		else {
			//std::cout << "r-" << "  ";
			z_l = disableY;
			if (camera.yaw > 0) {
				z_f = disableY;
			}
			else {
				z_b = disableY;
			}
		}
	}
	camera.Cmax.z -= workOffset;
	camera.Cmin.z -= workOffset;
	if (world[int(floor(camera.Cmin.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmin.y))][int(floor(camera.Cmin.z))]) {
		if (camera.yaw < 1.5708f && camera.yaw > -1.5708f) {
			//std::cout << "l+" << "  ";
			zz_l = disableY;
			if (camera.yaw > 0) {
				zz_b = disableY;
			}
			else {
				zz_f = disableY;
			}
		}
		else {
			//std::cout << "l-" << "  ";
			zz_r = disableY;
			if (camera.yaw > 0) {
				zz_b = disableY;
			}
			else {
				zz_f = disableY;
			}
		}
	}
	camera.Cmin.z += workOffset;

	camera.Cmax.y += workOffset + camera.Cforhead;
	if (world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmin.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmax.z))] or world[int(floor(camera.Cmax.x))][int(floor(camera.Cmax.y))][int(floor(camera.Cmin.z))]) {
		y = glm::vec3(1, 0, 1);
	}
	camera.Cmax.y += workOffset - camera.Cforhead;

	//if (!(x_f * xx_f * z_f * zz_f * x_b * xx_b * z_b * zz_b * z_r * zz_r * x_r * xx_r * z_l * zz_l * x_l * xx_l).x * !(x_f * xx_f * z_f * zz_f * x_b * xx_b * z_b * zz_b * z_r * zz_r * x_r * xx_r * z_l * zz_l * x_l * xx_l).z) {
	//	glm::vec3 center = glm::vec3((camera.Cmin.x + camera.Cmax.x) / 2, camera.Cmin.y, (camera.Cmin.z + camera.Cmax.z) / 2);
	//	if (world[int(floor(center.x))][int(floor(center.y))][int(floor(center.z))]){
	//		if (!world[int(floor(center.x))][int(floor(center.y)) + 1][int(floor(center.z))]) {
	//			camera.Position.y += camera.timeDelta*2.0f;
	//			std::cout << 1;
	//		}
	//	}
	//}
	
	//std::cout << camera.pitch << " | " << camera.yaw << std::endl;
	//std::cout << std::endl;
	//camera.Inputs(window, x_f * xx_f * z_f * zz_f, x_b * xx_b * z_b * zz_b, z_r * zz_r * x_r * xx_r, z_l * zz_l * x_l * xx_l, y);  //normal input
	camera.Inputs(window,allow, allow, allow, allow, allow);  //spectator input
}