#pragma once
#ifndef MP_HPP
#define MP_HPP

#include"libs.h"


class MousePicker
{
private:
	glm::vec3 currentRay;
	glm::mat4 viewMatrix;

	int width;
	int height;

	//functions

	//from viewport space to normalized device space
	glm::vec2 getNormaliizedDeviceCoord(double mX, double mY)
	{
		
		float x = (2.f * mX) /  width - 1;
		float y = (2.f * mY) / height - 1;
		return glm::vec2(x, -y);
	}
	
	//convert to eye coord
	glm::vec4 toEyeCoords(glm::vec4 clipCoords, glm::mat4 projection)
	{
		glm::mat4 invertedProjection = glm::inverse(projection);
		glm::vec4 eyeCoords = invertedProjection * clipCoords;
		eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
		return eyeCoords;
	}
	//convert to world space
	glm::vec3 toWorldSpace(glm::vec4 eyeCoords)
	{
		glm::mat4 invertedView = glm::inverse(this->viewMatrix);
		glm::vec4 rayWorld = invertedView * eyeCoords;
		glm::vec3 worldCoords = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
		//worldCoords = glm::normalize(worldCoords);
		return worldCoords;
	}

	glm::vec3 calculateMouseRay(double mouseX, double mouseY, glm::mat4 projection)
	{
		glm::vec2 normalizedCoord = getNormaliizedDeviceCoord(mouseX, mouseY);
		glm::vec4 clipCoords = glm::vec4(normalizedCoord.x, normalizedCoord.y, -1.f, 1.f);
		glm::vec4 eyeCoords = toEyeCoords(clipCoords, projection);
		glm::vec3 mouseRay = toWorldSpace(eyeCoords);
		
		return mouseRay;
	}


public:
	MousePicker(glm::mat4 viewMatrix, int width, int height)
	{
		this->viewMatrix = viewMatrix;
		this->width = width;
		this->height = height;
	}
	
	~MousePicker() {}

	//accessors
	inline glm::vec3 getCurrentRay()
	{
		return this->currentRay;
	}

	void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix,  double mouseX, double mouseY)
	{
	
		this->viewMatrix = viewMatrix;
		currentRay = calculateMouseRay(mouseX, mouseY, projectionMatrix);

	}

};

#endif MP_HPP
