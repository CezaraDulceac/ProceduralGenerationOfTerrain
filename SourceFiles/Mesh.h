#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Primitives.h"
#include "halfEdgeMesh.h"

class Mesh
{
private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	//halfedge
	CMU462::HalfedgeMesh he_mesh;
	std::vector<size_t> he_indices;
	std::vector< std::vector<size_t> > he_polygons;
	std::vector<glm::vec3>he_vertexPositions;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initHalfEdgeMesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
	{
		he_indices.clear();
		he_polygons.clear();
		he_vertexPositions.clear();

		for (int i = 0; i < nrOfIndices; i+=3)
		{
			he_indices.push_back(indexArray[i]);
			he_indices.push_back(indexArray[i+1]);
			he_indices.push_back(indexArray[i+2]);

			he_polygons.push_back(he_indices);
			he_indices.clear();
		}
		
		for (int i = 0; i < nrOfVertices; i++)
		{
			he_vertexPositions.push_back(vertexArray[i].position);
		}

		he_mesh.build(he_polygons, he_vertexPositions);
		
	}
	void initVertexData(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
	{
		this->vertices.clear();
		this->indices.clear();

		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertexArray[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indexArray[i]);
		}
	}

	void initVertexData(Primitive* primitive)
	{
		for (size_t i = 0; i < primitive->getNrOfVertiecs(); i++)
		{
			this->vertices.push_back(primitive->getVertices()[i]);
		}

		for (size_t i = 0; i < primitive->getNrOfIndices(); i++)
		{
			this->indices.push_back(primitive->getIndices()[i]);
		}
	}

	void initVAO(Primitive * primitive)
	{

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, primitive->getNrOfVertiecs() * sizeof(Vertex), primitive->getVertices(), GL_DYNAMIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitive->getNrOfIndices() * sizeof(GLuint), primitive->getIndices(), GL_DYNAMIC_DRAW);

		//SET VERTEX ATTRIB POINTERS AMD ENABLE - INPUT ASSEMBLY
		//GLuint attribLoc = glGetAttribLocation(core_programe, "vertex_position"); --in case we dont use location in shader
		//pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//texCoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//bind VAO 0
		glBindVertexArray(0);
	}

	void initVAO()
	{

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		GLuint* a = indices.data();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);

		//SET VERTEX ATTRIB POINTERS AMD ENABLE - INPUT ASSEMBLY
		//GLuint attribLoc = glGetAttribLocation(core_programe, "vertex_position"); --in case we dont use location in shader
		//pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//texCoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//bind VAO 0
		glBindVertexArray(0);
	}

	void updateUniforms(Shader* shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix()
	{
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

public:

	Mesh(Vertex* vertexArray, int nrOfVertices, GLuint* indexArray, int nrOfIndices,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
		)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->initVAO();
		this->updateModelMatrix();
		initHalfEdgeMesh(vertexArray, nrOfVertices, indexArray, nrOfIndices);
	}

	Mesh(Primitive* primitive,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
	)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVertexData(primitive);
		this->initVAO(primitive);
		this->updateModelMatrix();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	//accessors
	inline glm::vec3 getPosition()
	{
		return this->position;
	}

	inline glm::vec3 getRotation()
	{
		return this->rotation;
	}

	inline glm::vec3 getScale()
	{
		return this->scale;
	}

	inline glm::mat4 getModelMatrix()
	{
		return this->ModelMatrix;
	}

	inline void seeVerticesAndIndices()
	{
		std::cout << "Vertices number :" << vertices.size() << std::endl;
		for (auto a : vertices)
		{
			std::cout << a.position.x << " " << a.position.y << " " << a.position.z << std::endl;
		}

		std::cout << "Indices number :" << indices.size() << std::endl;
		for (auto a : indices)
		{
			std::cout << a << std::endl;
		}
	}
	//modifiers
	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}

	void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}

	void setScale(const glm::vec3 scale)
	{
		this->scale = scale;
	}

	//functions
	void move(const glm::vec3 position)
	{
		this->position += position;
	}

	void rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;
	}

	void scaleUp(const glm::vec3 scale)
	{
		this->scale += scale;
	}
	
	void render(Shader* shader)
	{
		//update uniforms
		this->updateModelMatrix();
		this->updateUniforms(shader);

		shader->use();

		//bind VAO
		glBindVertexArray(this->VAO);

		//RENDER
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);


	}

	void update(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
	{
		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->initVAO();
		this->updateModelMatrix();
		initHalfEdgeMesh(vertexArray, nrOfVertices, indexArray, nrOfIndices);
	}

	void printMesh()
	{
		//he_mesh.printVerteces();
	}

	std::vector<glm::vec3> findNeighbours(glm::vec3 vertex)
	{
		return he_mesh.findNeighbours_CMU(vertex);
	}

	std::vector<glm::vec3> tryThis(glm::vec3 vertex, int size)
	{
		//vector<vector<CMU462::VertexCIter>>vec;
		return he_mesh.dfsV(vertex, size);
	}
};

#endif MESH_HPP