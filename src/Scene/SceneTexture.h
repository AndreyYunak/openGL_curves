#pragma once

#include <array>
#include <filesystem>
#include "Scene.h"
#include "imgui.h"
#include "3D_curves/3D_curves.h"
#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"
//#include "../Model.h"
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
//#include "../camera.h"



namespace scene {

	class SceneTexture : public Scene
	{
	public:
		SceneTexture();
		~SceneTexture();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;


	private:
		std::array<float, 32> vertices = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		std::array<unsigned int, 6> indices = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		VertexArray vao;
		VertexBuffer vbo;
		VertexBufferLayout layout_f;
		IndexBuffer ibo;
		//IndexBuffer ibo(indices.data(), indices.size());
		//Shader& ourShader;
		Shader sceneShader;
		unsigned int texture1, 
					 texture2;
		unsigned int modelLoc, 
					 viewLoc, 
					 projectionLoc;
		glm::mat4 projection,
				  view, 
				  model = glm::mat4(1.0f);
	


	};

	class SceneTextureSimple : public Scene
	{
	public:
		SceneTextureSimple();
		~SceneTextureSimple();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

	private:
		Shader* sceneShader = new Shader("./Shader/shader_texture.vs", "./Shader/shader_texture.frag");
		float vertices[32] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[6] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		unsigned int VBO, VAO, EBO;
		unsigned int texture1, texture2;
		
	};
}