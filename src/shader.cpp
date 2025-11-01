#include "shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	
	unsigned int vertexShader;

	const char* vShaderCode = readShaderCode(vertexShaderPath);
	
	vertexShader = compileShader(vShaderCode, GL_VERTEX_SHADER);
	
	unsigned int fragmentShader;
	
	const char* fShaderCode = readShaderCode(fragmentShaderPath);

	fragmentShader = compileShader(fShaderCode, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();

	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

const char* Shader::readShaderCode(const char* filePath) {

	std::ifstream shaderFile;

	// Ensure ifstream objects can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {

		shaderFile.open(filePath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	return shaderCode.c_str();

}

unsigned int Shader::compileShader(const char* shaderCode, const int SHADER_TYPE) {

	unsigned int shader;

	shader = glCreateShader(SHADER_TYPE);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << SHADER_TYPE << "COMPILATION_FAILED\n" << infoLog << std::endl;

	}

	return shader;

}

void Shader::use() {
	glUseProgram(programId);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}