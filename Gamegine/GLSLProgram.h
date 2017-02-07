#pragma once

#include<GL/glew.h>
#include<iostream>

namespace Gamegine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		//shader operation
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		//
		void linkerShaders();

		//
		void addAtrribute(const std::string& attributeName);

		//Get the uniform color(corresponding to the file(.frag) inside Shaders)(GLuint-->unsigned int)
		GLint getUniformLocation(const std::string& uniformName);


		//use or unuse
		void use();
		void unuse();
	private:
		void compileShader(const std::string& filePath, GLuint& id);
		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		GLuint _numAttributes;
	};

}