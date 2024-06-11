#pragma once

#include <functional>
#include <vector>
#include <string>
#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <memory>

//#include "../../external/3D_curves/3D_curves.h"
#include "../../3D_curves/include/3D_curves/3D_curves.h"
#include "../Renderer/ShaderProgram.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "Renderer/stb_image.h"
//#include "../camera.h"
#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace scene {

	class Scene
	{

	public:
		Scene() {};
		virtual ~Scene() {};
	
		virtual void onRender() {};
		virtual void onUpdate(float deltaTime) {};
		virtual void onImGuiRender() {};
	};

	class SceneMenu : public Scene
	{

	public:
		SceneMenu(Scene*& CurrentScenePointer);
		~SceneMenu() {};

		template<typename T>
		void RegScene(const std::string& name)
		{
			std::cout << "Registering Scene: " << name << std::endl;
			m_Scene.push_back(std::make_pair(name, []() {return new T(); }));
		}
	
		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

	private:
		Scene*& m_CurrentScene;
		std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scene;
	};
}