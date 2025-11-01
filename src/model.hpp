#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"
#include "shader.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model {

private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded; //stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	bool gammaCorrection;

	Model(std::string const& path, bool gamma = false);
	void Draw(Shader& shader);

};
