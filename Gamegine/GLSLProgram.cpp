#include "GLSLProgram.h"
#include<iostream>
#include<fstream>
#include "Errors.h"
#include<vector>

namespace Gamegine {
	GLSLProgram::GLSLProgram() :_numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{

	}


	//const protects the variable not be changed,if changed,all the values will be changed simutaneously
	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		//the first line also could be put in linker()
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.
		//Get a program object.
		_programID = glCreateProgram();


		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (0 == _vertexShaderID)
		{
			fatalError("vertex shader failed to be created!");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (0 == _fragmentShaderID)
		{
			fatalError("Fragment shader failed to be created!");
		}

		//self defined function for compiling shaders
		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);


	}


	//from the google,input shader compile,then you get the page of shader compiling and the following codes
	void GLSLProgram::linkerShaders()
	{


		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &errorLog[0]);
			fatalError("shader failed to link!");
		}
		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		//Don't leak
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}


	void GLSLProgram::compileShader(const std::string& filePath, GLuint& id)
	{
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			perror(filePath.c_str());
			fatalError("Failed to open" + filePath);
		}

		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}
		vertexFile.close();

		//const means that the pointed to could not be changed
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (GL_FALSE == success)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//the max length includes the null character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);


			//provide the infolog in whatever manor you deem best
			//Exit with failure
			glDeleteShader(_vertexShaderID);//donnot leak the shader

			std::printf("%s\n", &errorLog[0]);
			fatalError("shader" + filePath + "failed to compile!");

		}
	}



	void GLSLProgram::addAtrribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
		_numAttributes++;
	}


	//use
	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0;i < _numAttributes;i++)
		{
			glEnableVertexAttribArray(i);

		}
	}

	//unuse
	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0;i < _numAttributes;i++)
		{
			glDisableVertexAttribArray(i);

		}
	}


	//Get the uniform color(corresponding to the file(.frag) inside Shaders)
	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (GL_INVALID_INDEX == location)
		{
			fatalError("UniformName" + uniformName + "not found in shader!");
		}
		return location;

	}

}