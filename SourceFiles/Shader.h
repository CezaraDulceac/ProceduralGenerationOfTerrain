#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
private:
	//member variables
	GLuint id;

	//private functions
	std::string loadShaderSource(char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::fstream in_file;

		//vertex
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				src += temp + "\n";
			}
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName <<  std::endl;
		}

		in_file.close();

		return src;
	}

	GLuint loadShader(GLenum type,char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();

		glShaderSource(shader, 1, &src, NULL); //set the source the new vertex
		glCompileShader(shader);

		//error verification
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog); //get the infolog about the shader
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << std::endl;
			std::cout << infoLog << std::endl;
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		//attach shaders to program
		glAttachShader(this->id, vertexShader);
		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}
		glAttachShader(this->id, fragmentShader);

		//link program
		glLinkProgram(this->id);

		//error check
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog); //get the infolog about the shader
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;
			std::cout << infoLog << std::endl;
		}

		glUseProgram(0);
	}

public:

	//constructor / destructor
	Shader(char* vertexFile, char* fragmentFile, char* geometryFile)
	{
		if (NULL != vertexFile && NULL != fragmentFile && NULL != geometryFile)
		{
			GLuint vertexShader = 0;
			GLuint geometryShader = 0;
			GLuint fragmentShader = 0;

			vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
			if (geometryFile != "")
			{
				geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
			}
			fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

			this->linkProgram(vertexShader, geometryShader, fragmentShader);

			//End
			glDeleteShader(vertexShader);
			glDeleteShader(geometryShader);
			glDeleteShader(fragmentShader);
		}
		else
		{
			std::cout << "ERROR::SHADER::CONSTRUCTOR" << std::endl;
		}
		
	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	//set uniform functions
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	//for sending uniforms
	void set1i(GLfloat value, const GLchar* name) //for textures
	{
		this->use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}
	void setVec1f(GLfloat value, const GLchar* name)
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
		this->unuse();
	}

};

#endif SHADER_HPP;