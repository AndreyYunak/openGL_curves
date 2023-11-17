#include "ShaderProgram.h"

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path)
{
	// 1. ������� �������� ��� �������� �� PATH 
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		//��������� �����
		vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		//��������� ������ � ������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//��������� �����
		vShaderFile.close();
		fShaderFile.close();
		//��������������� ������ � ������ GLchar
		vertex_code = vShaderStream.str();
		fragment_code = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertex_code.c_str();
	const GLchar* fShaderCode = fragment_code.c_str();

	//	2. ������ ��������
	GLint success;
	GLchar infoLog[512];
	// ��������� ������
	GLuint vs = glCreateShader(GL_VERTEX_SHADER); //������� ������ � ����� GL_VERTEX_SHADER. ������ ��� ������������� � vs
	glShaderSource(vs, 1, &vShaderCode, NULL);
	glCompileShader(vs);
	// ���� �� ������?
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILD: " << infoLog << std::endl;
	};
	// ����������� ������
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fShaderCode, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILD: " << infoLog << std::endl;
	};

	//��������� ���������
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vs);
	glAttachShader(this->Program, fs);
	glLinkProgram(this->Program);
	//ERROR 
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
	};
	//������� �������
	glDeleteShader(vs);
	glDeleteShader(fs);

}

void Shader::Use()
{
	glUseProgram(this->Program);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->Program, name.c_str()), value);
}

Shader::~Shader() {
	glDeleteProgram(this->Program);
};
