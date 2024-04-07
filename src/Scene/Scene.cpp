#include "Scene.h"

namespace scene
{

	SceneMenu::SceneMenu(Scene*& CurrentScenePointer)
		: m_CurrentScene(CurrentScenePointer) {}

	void SceneMenu::onRender()
	{
	}
	void SceneMenu::onUpdate(float deltaTime)
	{
	}
	void SceneMenu::onImGuiRender()
	{
		for (auto& scene : m_Scene)
		{
			if (ImGui::Button(scene.first.c_str()))
				m_CurrentScene = scene.second();
		}
	}
}