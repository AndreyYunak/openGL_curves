#include "ShaderProgram.h"

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path)
{
	// 1. ПОЛУЧЕМ ИСХОДНЫЙ КОД ШЕЙДЕРОВ ИЗ PATH 
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		//Открываем файлы
		vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		//Считываем данные в потоки
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//Закрываем файлы
		vShaderFile.close();
		fShaderFile.close();
		//Преобразовываем потоки в массив GLchar
		vertex_code = vShaderStream.str();
		fragment_code = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertex_code.c_str();
	const GLchar* fShaderCode = fragment_code.c_str();

	//	2. СБОРКА ШЕЙДЕРОВ
	GLint success;
	GLchar infoLog[512];
	// Вершинный шейдер
	GLuint vs = glCreateShader(GL_VERTEX_SHADER); //создаем шейдер с типом GL_VERTEX_SHADER. Храним его идентификатор в vs
	glShaderSource(vs, 1, &vShaderCode, NULL);
	glCompileShader(vs);
	// Есть ли ошибки?
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILD: " << infoLog << std::endl;
	};
	// Фрагментный шейнер
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fShaderCode, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILD: " << infoLog << std::endl;
	};

	//Шейдерная программа
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
	//Удаляем шейдеры
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
