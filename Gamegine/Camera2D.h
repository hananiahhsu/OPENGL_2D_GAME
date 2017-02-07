#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	
	//update your cameras
	void update();
	//set the pos of camera2d
	void setPosition(const glm::vec2& newPosition) 
	{
		position = newPosition;
	}
	//get the pos of camera2d
	glm::vec2 getPosition()
	{
		return position;
	}
	//set the scale of camera2d
	void  setScale(float newScale)
	{
		scale = newScale;
	}
	//get the scale
	float getScale()
	{
		return scale;
	}
	//get the camera Matrix
	glm::vec4 getCameraMatrix()
	{
		return cameraMatrix;
	}
	//init the screen parameter
	void init(int screenWidth, int screenHeight);

private:
	int _screenHeight, _screenWidth;
	bool needsCameraUpdate;
	//zoom in or out
	float scale;
	glm::vec2 position;
	glm::vec4 cameraMatrix;

};

