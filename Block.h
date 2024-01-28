#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>

#include <unordered_map>

//GLfloat block[] = {
//	0.0f,	0.0f,	0.0f,		0.0f,	0.0f,		0.0f, -1.0f, 0.0f, //y-
//	0.0f,	0.0f,	1.0f,		1.0f,	0.0f,		0.0f, -1.0f, 0.0f,
//	1.0f,	0.0f,	0.0f,		0.0f,	1.0f,		0.0f, -1.0f, 0.0f,
//	1.0f,	0.0f,	1.0f,		1.0f,	1.0f,		0.0f, -1.0f, 0.0f,
//
//	0.0f,	0.0f,	0.0f,		0.0f,	0.0f,		-1.0f, 0.0f, 0.0f,//x-
//	0.0f,	0.0f,	1.0f,		0.0f,	1.0f,		-1.0f, 0.0f, 0.0f,
//	0.0f,	1.0f,	0.0f,		1.0f,	0.0f,		-1.0f, 0.0f, 0.0f,
//	0.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		-1.0f, 0.0f, 0.0f,
//
//	0.0f, 	0.0f,	0.0f,		0.0f,	0.0f,		0.0f, 0.0f, -1.0f,//z-
//	0.0f,	1.0f,	0.0f,		0.0f,	1.0f,		0.0f, 0.0f, -1.0f,
//	1.0f,	0.0f,	0.0f,		1.0f,	0.0f,		0.0f, 0.0f, -1.0f,
//	1.0f,	1.0f,	0.0f,		1.0f,	1.0f,		0.0f, 0.0f, -1.0f,
//
//	0.0f,	1.0f,	0.0f,		0.0f,	0.0f,		0.0f, 1.0f, 0.0f,//y+
//	0.0f,	1.0f,	1.0f,		1.0f,	0.0f,		0.0f, 1.0f, 0.0f,
//	1.0f,	1.0f,	0.0f,		0.0f,	1.0f,		0.0f, 1.0f, 0.0f,
//	1.0f,	1.0f,	1.0f,		1.0f,	1.0f,		0.0f, 1.0f, 0.0f,
//
//	1.0f,	0.0f,	0.0f,		0.0f,	0.0f,		1.0f, 0.0f, 0.0f,//x+
//	1.0f,	0.0f,	1.0f,		0.0f,	1.0f,		1.0f, 0.0f, 0.0f,
//	1.0f,	1.0f,	0.0f,		1.0f,	0.0f,		1.0f, 0.0f, 0.0f,
//	1.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		1.0f, 0.0f, 0.0f,
//
//	0.0f,	0.0f,	1.0f,		0.0f,	0.0f,		0.0f, 0.0f, 1.0f,//z+
//	1.0f,	0.0f,	1.0f,		1.0f,	0.0f,		0.0f, 0.0f, 1.0f,
//	0.0f,	1.0f,	1.0f,		0.0f,	1.0f,		0.0f, 0.0f, 1.0f,
//	1.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		0.0f, 0.0f, 1.0f
//};

class Block {
	public:
		enum Faces {
			XP,
			XM,
			YP,
			YM,
			ZP,
			ZM
		};

		struct FaceData {
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uv;
			//std::vector<glm::vec3> normals;
		};

		struct RawFaceData {
			static std::unordered_map < Faces, std::vector < glm::vec3>> rawVertexData;		//vertices only for now
		};

		std::vector<glm::vec2> UV = {
			glm::vec2(0.0f,	0.0f),
			glm::vec2(1.0f,	0.0f),
			glm::vec2(0.0f,	1.0f),
			glm::vec2(1.0f,	1.0f)
		};

		glm::vec3 position;

		std::unordered_map<Faces, FaceData> faces;
		
		Block(glm::vec3 Position);
		std::vector<glm::vec3> AddTransformedVertices(std::vector<glm::vec3> vertices);
		FaceData GetFace(Faces face);
};

#endif;
