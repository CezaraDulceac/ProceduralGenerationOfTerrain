#pragma once
#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <vector>
#include "Vertex.h"
#include <glew.h>
#include <glfw3.h>


class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


public:
	Primitive() {}
	virtual ~Primitive() {}

	//functions
	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices()
	{
		return this->vertices.data();
	}

	inline GLuint* getIndices()
	{
		return this->indices.data();
	}

	inline const unsigned getNrOfVertiecs()
	{
		return this->vertices.size();
	}

	inline const unsigned getNrOfIndices()
	{
		return this->indices.size();
	}
};

class Triangle : public Primitive
{
public:
	Triangle()
		:Primitive()
	{
		Vertex vertices[] =
		{
			//position						//color						    //texCoord				//normals
			glm::vec3(-0.5f, 0.0f, -0.5f),  glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, 0.0f, 0.5f),	glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),   	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.0f, 0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f)

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Quad : public Primitive
{
public:

	Quad()
		:Primitive()
	{
		Vertex vertices[] =
		{
			//pos							//color						    //texCoord				//normals
			glm::vec3(-0.5f, 0.0f, -0.5f),  glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, 0.0f, 0.5f),	glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),   	glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.0f, 0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.0f, -0.5f),	glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2, //for creating triangles
			0, 2, 3
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Plan : public Primitive
{
public:

	Plan()
		:Primitive()
	{
		Vertex vertices[] =
		{
			//pos							//color						    //texCoord				//normals
			glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),//0--1
			glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),   	glm::vec3(0.f, 0.f, 1.f),//1-0
			glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),//2-0
			glm::vec3(0.5f, 0.5f, 0.0f),	glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//3--1

			glm::vec3(1.5f, 0.5f, 0.0f),	glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//4--1
			glm::vec3(1.5f, -0.5f, 0.0f),	glm::vec3(1.f, 1.f, 1.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//5-0
			glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//6---1
			glm::vec3(-0.5f, -1.5f, 0.0f),	glm::vec3(0.f, 1.f, 1.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//7---1
			glm::vec3(0.5f, -1.5f, 0.0f),	glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),//8
			glm::vec3(1.5f, -1.5f, 0.0f),	glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)//9

		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2, //for creating triangles
			0, 2, 3,
			3, 2, 5,
			3, 5, 4,
			6, 7, 8,
			6, 8, 2,
			2, 8, 9,
			2, 9, 5
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

#endif PRIMITIVE_HPP