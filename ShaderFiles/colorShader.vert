#version 400


in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;




out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;



void main()
{
  //set x and y coord on the screen
  gl_Position.xy = vertexPosition; 
  //It's clear that we are now in 2D game ,so z == 0
  gl_Position.z = 0.0;
  //indicate that the x,y,z value are normalized
  gl_Position.w = 1;


  fragmentColor = vertexColor;
  fragmentPosition  = vertexPosition;
  fragmentUV = vertexUV;

}
