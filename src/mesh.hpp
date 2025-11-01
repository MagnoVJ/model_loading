#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "shader.hpp"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 Position;  //position
	glm::vec3 Normal;    //normal
	glm::vec2 TexCoords; //texture coordinates
	glm::vec3 Tangent;   //tangent
	glm::vec3 Bitangent; //bitangent
	int BoneIDs[MAX_BONE_INFLUENCE];  //bone indexes which will influence this vertex
	float Weights[MAX_BONE_INFLUENCE];//weights from each bone 
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {

private:
	// render data
	unsigned int VBO, EBO;
	// initializes all the buffer objects/arrays
	void setupMesh();

public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;
	unsigned int VAO;
	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	// render the mesh
	void Draw(Shader& shader);

};