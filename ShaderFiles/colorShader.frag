#version  400
//The range of operation lies inside the given polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;



//for each pixel given the outputed components
out vec4 output_color;

uniform float time;
uniform sampler2D catSampler;




void main()
{
  //RGBA
  vec4 textureColor = texture(catSampler,fragmentUV);





  //You can set a fixed value for the output color
  output_color = fragmentColor + vec4(fragmentPosition.x * (cos(time)+ 0.6) * 0.3,
                                      fragmentPosition.y * (sin(time)+ 1.6) * 0.8,
									  fragmentPosition.x * (cos(time)+ 0.5) * 0.6,
									  fragmentColor.a);
}  