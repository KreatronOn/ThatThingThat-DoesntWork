#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"Block.h"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"ShaderClass.h"
#include"Texture.h"

class Chunk {
	private:
		std::vector<glm::vec3> chunkVerts;
		std::vector<glm::vec2> chunkUVs;
		std::vector<int> chunkIndices;

		glm::uint indexCount;

	public:
		VAO chunkVAO;
		VBO chunkVertexVBO;
		VBO chunkUVVBO;
		EBO chunkEBO;
		Texture texture;

		const int SIZE = 16;
		const int HEIGHT = 128;

		glm::vec3 position;

		Chunk(glm::vec3 Position);

		//void GenChunk();
		void GenBlocks();
		void AddIndices(int amntFaces);
		void BuildChunk();
		void Render(Shader& shader);
		void Delete();
};

#endif