#pragma once

#include <functional>
#include <vector>
#include <string>
#include <imgui.h>

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