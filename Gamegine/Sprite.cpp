#include "Sprite.h"

#include "vertex.h"

#include<cstddef>//offset()
#include "resourceManager.h"

namespace Gamegine {
	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (0 != _vboID)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}


	//init 
	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		//get the texture
		_texture = resourceManager::getTexture(texturePath);




		if (0 == _vboID)
		{
			//generate the buffer with size needed
			glGenBuffers(1, &_vboID);
		}
		//this array will hold current vertex data
		//we need 6 vertices,each vertex has 2
		//floats for x and y
		//float vertexData[12];//after the struct of vertex is defined,we use vertex to define our data
		vertex vertexData[6];

		//vertexData[0].position.x = x + width;
		//vertexData[0].position.y = y + height;
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		//vertexData[1].position.x = x;
		//vertexData[1].position.y = y + height;
		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);


		//vertexData[2].position.x = x;
		//vertexData[2].position.y = y;
		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);


		//second triangle
		//vertexData[3].position.x = x ;
		//vertexData[3].position.y = y ;
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		//vertexData[4].position.x = x + width;
		//vertexData[4].position.y = y;
		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		//vertexData[5].position.x = x + width;
		//vertexData[5].position.y = y + height;
		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);



		for (int i = 0;i < 6;i++)
		{
			//vertexData[i].color.r = 255;
			//[i].color.g = 0;
			//vertexData[i].color.b = 255;
			//vertexData[i].color.a = 255;
			//struct your code works very important
			vertexData[i].setColor(255, 0, 255, 255);
		}
		/*
			vertexData[1].color.r = 0;
			vertexData[1].color.g = 0;
			vertexData[1].color.b = 255;
			vertexData[1].color.a = 255;

			vertexData[4].color.r = 0;
			vertexData[4].color.g = 255;
			vertexData[4].color.b = 0;
			vertexData[4].color.a = 255;
		*/
		vertexData[1].setColor(0, 0, 255, 255);
		vertexData[4].setColor(0, 255, 0, 255);//error here ,notice the script of vertexData





		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);



	}
	//draw
	void Sprite::draw()
	{
		//0.bind the texture
		glBindTexture(GL_TEXTURE_2D, _texture._id);


		//1.bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//2.Tell opengl that we want to use
		//the first array,we only need one array right now
		//since we use only position
		glEnableVertexAttribArray(0);
		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
		//This is the color attribute pointer(range:0~255)
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));//first attribute,so the first param is 1 

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));//second attribute


		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//Disable the vertex attribute array and this is not optional
		//unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

}