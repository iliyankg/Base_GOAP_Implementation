#pragma once
#include <glm.hpp>


class MNode
{
public:
	MNode(int id, glm::vec3 _pos) { _id = id; _pos = _position; }
	~MNode() {}

	int _id;
	glm::vec3 _position;
};