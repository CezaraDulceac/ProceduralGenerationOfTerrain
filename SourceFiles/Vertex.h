#pragma once
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

#endif VERTEX_HPP