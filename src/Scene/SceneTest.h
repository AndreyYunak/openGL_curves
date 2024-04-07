#pragma once

#include "Scene.h"
#include "imgui.h"
#include "3D_curves/3D_curves.h"
#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"

namespace scene {


	class SceneTest : public Scene 
	{
	public:
		SceneTest();
		~SceneTest();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

	private:
		

	};


	class SceneCurves : public Scene
	{
	public:
		SceneCurves();
		~SceneCurves();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

		Geometric_curves_3D* AddCurves(Geometric_curves_3D* circle);

	private:
		//std::vector<std::pair<Geometric_curves_3D*, std::vector<point3D>* > > curves;
		std::vector<Geometric_curves_3D*> curves;
		std::vector<point3D> v;

		VertexArray va_c;

	};

}