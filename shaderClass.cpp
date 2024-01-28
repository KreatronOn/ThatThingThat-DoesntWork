#include"shaderClass.h"
#include <vector>

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		//vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);	//vertex shader compilation errors
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
	}



	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		//fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);


	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);	//fragment shader compilation errors
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
	}




	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);		//attaching shader to shader program
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);


	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed: " << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind() {
	glUseProgram(ID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}
