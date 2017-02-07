#pragma once

#include <GL/glew.h>

namespace Gamegine {
	struct position
	{
		float x;
		float y;
	};

	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};


	struct UV
	{
		float u;
		float v;
	};



	//the vertex struct
	struct vertex {
		//This is the position struct.when you store a struct or class
		//inside of another struct or class,it is called composiiton;
		//This is layed out exactly the same in memory as if we had a float position[2].
		//but doing it this way makes more sense.

		position position;

		//4 bytes for r g b a
		Color color;

		//uv texture coordinates(0-1,texture mapping)
		UV uv;

		//set the color of (related with texture mapping)
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}


		//set the color of uv
		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		//set the position
		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}


	};


}