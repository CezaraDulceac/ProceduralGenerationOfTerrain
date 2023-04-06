#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <fstream>
#include <string>

#include <glew.h>
#include <glfw3.h>
#include <SOIL2.h>

class Texture
{
private:
	GLuint id;
	int height;
	int width;
	unsigned int type;


public:
	Texture(const char* fileName, GLenum type)
	{

		this->type = type;
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		GLuint texture0;
		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT); //if texture is too small, repeat it
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //antialising for texture
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type); //change sizes of images - perspective
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << fileName << std::endl;
		}

		glActiveTexture(0); //make no active texture unit
		glBindTexture(type, 0); //unbind texture 
		SOIL_free_image_data(image);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getId() const
	{
		return this->id;
	}

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	void loadFromFile(const char* fileName)
	{
		if (this->id)
		{
			glDeleteTextures(1, &this->id);
		}

		this->type = type;
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		GLuint texture0;
		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT); //if texture is too small, repeat it
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //antialising for texture
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type); //change sizes of images - perspective
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FROM_FILEFAILED: " << fileName << std::endl;
		}

		glActiveTexture(0); //make no active texture unit
		glBindTexture(this->type, 0); //unbind texture 
		SOIL_free_image_data(image);
	}
};

#endif TEXTURE_HPP