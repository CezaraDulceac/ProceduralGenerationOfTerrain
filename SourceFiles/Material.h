#pragma once
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"

class Material
{
private:
	//color and intensity
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	//textures
	GLint water;
	GLint sand;
	GLint dirt;
	GLint grass;
	GLint hill;
	GLint mountain;
	GLint snow;

public:

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint water, GLint sand, GLint dirt, GLint grass, GLint hill, GLint mountain, GLint snow)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->water = water;
		this->sand = sand;
		this->sand = sand;
		this->dirt = dirt;
		this->grass = grass;
		this->hill = hill;
		this->mountain = mountain;
		this->snow = snow;
	}

	~Material(){}

	//functions
	void sendToShader(Shader& program)
	{
		program.setVec3f(this->ambient,  "material.ambient");
		program.setVec3f(this->diffuse,  "material.diffuse");
		program.setVec3f(this->specular, "material.specular");
		program.set1i(this->water,  "material.water");
		program.set1i(this->sand, "material.sand");
		program.set1i(this->dirt, "material.dirt");
		program.set1i(this->grass, "material.grass");
		program.set1i(this->hill, "material.hill");
		program.set1i(this->mountain, "material.mountain");
		program.set1i(this->snow, "material.snow");
	}
};

#endif MATERIAL_HPP