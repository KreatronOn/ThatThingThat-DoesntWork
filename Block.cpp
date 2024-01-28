#include"Block.h"
std::unordered_map<Block::Faces, std::vector<glm::vec3>> Block::RawFaceData::rawVertexData = {
	{Faces::XP, std::vector<glm::vec3>{
		glm::vec3(1.0f,	0.0f, 0.0f),
		glm::vec3(1.0f,	0.0f, 1.0f),
		glm::vec3(1.0f,	1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	}},
	{Faces::XM, std::vector<glm::vec3>{
		glm::vec3(0.0f,	0.0f, 0.0f),
		glm::vec3(0.0f,	0.0f, 1.0f),
		glm::vec3(0.0f,	1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f)
	}},
	{Faces::YP, std::vector<glm::vec3>{
		glm::vec3(0.0f,	1.0f, 0.0f),
		glm::vec3(0.0f,	1.0f, 1.0f),
		glm::vec3(1.0f,	1.0f, 0.0f),
		glm::vec3(1.0f,	1.0f, 1.0f)
	}},
	{Faces::YM, std::vector<glm::vec3>{
		glm::vec3(0.0f,	0.0f, 0.0f),
		glm::vec3(0.0f,	0.0f, 1.0f),
		glm::vec3(1.0f,	0.0f, 0.0f),
		glm::vec3(1.0f,	0.0f, 1.0f)
	}},
	{Faces::ZP, std::vector<glm::vec3>{
		glm::vec3(0.0f,	0.0f, 1.0f),
		glm::vec3(1.0f,	0.0f, 1.0f),
		glm::vec3(0.0f,	1.0f, 1.0f),
		glm::vec3(1.0f,	1.0f, 1.0f)
	}},
	{Faces::ZM, std::vector<glm::vec3>{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f,	1.0f, 0.0f),
		glm::vec3(1.0f,	0.0f, 0.0f),
		glm::vec3(1.0f,	1.0f, 0.0f)
	}}
};

Block::Block(glm::vec3 Position) {
	position = Position;

	faces = std::unordered_map<Faces, FaceData>{
		{Faces::XP, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::XP)),
			UV
		}},
		{Faces::XM, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::XM)),
			UV
		} },
		{Faces::YP, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::YP)),
			UV
		} },
		{Faces::YM, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::YM)),
			UV
		} },
		{Faces::ZP, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::ZP)),
			UV
		} },
		{Faces::ZM, FaceData{
			AddTransformedVertices(RawFaceData::rawVertexData.at(Faces::ZM)),
			UV
		} }
	};
}

std::vector<glm::vec3> Block::AddTransformedVertices(std::vector<glm::vec3> vertices) {
	std::vector<glm::vec3> transformedVertices = std::vector<glm::vec3>();
	for (const auto& vert : vertices) {
		transformedVertices.push_back(vert + position);
	}
	return transformedVertices;
}

Block::Block::FaceData Block::GetFace(Faces face) {
	return faces[face];
}