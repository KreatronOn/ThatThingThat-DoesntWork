#include"Chunk.h"

Chunk::Chunk(glm::vec3 Position) : chunkVertexVBO(chunkVerts), chunkUVVBO(chunkUVs),
chunkEBO(chunkIndices), texture("cob.png") {
	position = Position;



	GenBlocks();
	BuildChunk();
}
void Chunk::GenBlocks() {
	for (float x = 0.0f; x < 2; x++) {
		Block block(glm::vec3(x, 0.0f, 0.0f));
		Block::FaceData upFace = block.GetFace(Block::Faces::YP);
		chunkVerts.insert(chunkVerts.end(), upFace.vertices.begin(), upFace.vertices.end());
		chunkUVs.insert(chunkUVs.end(), upFace.uv.begin(), upFace.uv.end());

		AddIndices(1);
	}
}

void Chunk::AddIndices(int amntFaces) {
	for (int i = 0; i < amntFaces; i++) {
		chunkIndices.push_back(0 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(1 + indexCount);
		chunkIndices.push_back(1 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(3 + indexCount);

		indexCount += 4;
	}
}

void Chunk::BuildChunk() {
	chunkVAO.Bind();


	VBO chunkVertexVBO(chunkVerts);
	chunkVertexVBO.Bind();
	chunkVAO.LinkAttrib(0, 3, chunkVertexVBO);

	//VBO chunkUVVBO(chunkUVs);
	//chunkUVVBO.Bind();
	//chunkVAO.LinkAttrib(1, 2, chunkUVVBO);

	EBO chunkEBO(chunkIndices);

	//Texture texture("grass.png");
}

void Chunk::Render(Shader& shader) {
	shader.Bind();
	chunkVAO.Bind();
	chunkEBO.Bind();
	//texture.Bind();
	//texture.texUnit(shader, "tex0", 0);
	glDrawElements(GL_TRIANGLES, chunkIndices.size(), GL_UNSIGNED_INT, 0);
}

void Chunk::Delete() {
	chunkVAO.Delete();
	chunkVertexVBO.Delete();
	chunkUVVBO.Delete();
	chunkEBO.Delete();
	texture.Delete();
}
