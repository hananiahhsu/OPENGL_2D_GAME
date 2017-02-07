#include "Camera2D.h"



Camera2D::Camera2D():position(0.0f,0.0f),cameraMatrix(0.0f),scale(1.0f),needsCameraUpdate(true)
,_screenWidth(),_screenHeight()
{

}


Camera2D::~Camera2D()
{

}

void Camera2D::init(int screenWidth,int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}


void Camera2D::update()
{
	if (needsCameraUpdate)
	{

	}





}