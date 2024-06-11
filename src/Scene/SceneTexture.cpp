#include "SceneTexture.h"
#include "../Model.h"
//#include "../camera.h"

//extern Camera camera;

namespace scene
{
	 const unsigned int SCR_WIDTH = 800;
	 const unsigned int SCR_HEIGHT = 600;



	SceneTexture::SceneTexture() :	vao(),
									vbo(vertices.data(), sizeof(float)* vertices.size()), 
									ibo(indices.data(), indices.size()),
									sceneShader("./Shader/shader_texture.vs", "./Shader/shader_texture.frag")
	{
		vao.Bind();
		layout_f.Push<float>(3);
		layout_f.Push<float>(3);
		layout_f.Push<float>(2);
		vao.AddBuffer(vbo, layout_f);
		ibo.Bind();
		
		sceneShader.use();
		texture1 = GL::TextureFromFile("container.jpg", ".\\Shader");
		sceneShader.setInt("texture1", 0);
		texture2 = GL::TextureFromFile("awesomeface.png", ".\\Shader");
		sceneShader.setInt("texture2", 1);
		
		modelLoc = glGetUniformLocation(sceneShader.ID, "model");
		viewLoc = glGetUniformLocation(sceneShader.ID, "view");
		projectionLoc = glGetUniformLocation(sceneShader.ID, "projection");

		
		
		


		
		
		vao.Unbind();

		
	}

	SceneTexture::~SceneTexture()
	{
	}

	void SceneTexture::onRender()
	{
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		sceneShader.use();

		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// camera/view transformations
		
		//view = camera.GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
		sceneShader.setMat4("model", model);

		vao.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
		// //ibo->GetCount()
		//glDrawArrays(GL_TRIANGLES, 0, 4);

	}

	void SceneTexture::onUpdate(float deltaTime)
	{
	}

	void SceneTexture::onImGuiRender()
	{
		(ImGui::Button("Button TEST!"));
	}



	SceneTextureSimple::SceneTextureSimple() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLuint) * 6), &indices[0], GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		sceneShader->use();
		texture1 = GL::TextureFromFile("container.jpg", ".\\Shader");
		sceneShader->setInt("texture1", 0);
		texture2 = GL::TextureFromFile("awesomeface.png", ".\\Shader");
		sceneShader->setInt("texture2", 1);

	};
	SceneTextureSimple::~SceneTextureSimple() {};

	void SceneTextureSimple::onRender() {
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// render container
		sceneShader->use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_POINTS, 0, 4);

	};
	void SceneTextureSimple::onUpdate(float deltaTime) {
		
	};
	void SceneTextureSimple::onImGuiRender() {
	
	};

}
