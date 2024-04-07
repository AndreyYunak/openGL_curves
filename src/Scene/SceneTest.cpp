#include "SceneTest.h"

namespace scene
{



	SceneTest::SceneTest()
	{
	}

	SceneTest::~SceneTest()
	{
	}

	void SceneTest::onRender()
	{
	}

	void SceneTest::onUpdate(float deltaTime)
	{
	}

	void SceneTest::onImGuiRender()
	{
		(ImGui::Button("Button TEST!"));
	}




	SceneCurves::SceneCurves()
	{
		
	}

	SceneCurves::~SceneCurves()
	{
	}

	void SceneCurves::onRender()
	{
		va_c.Bind();
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::mat4(1.0f);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_POINTS, 0, v.size());
	}

	void SceneCurves::onUpdate(float deltaTime = 0)
	{
		va_c.Bind();
		VertexBuffer vb_c(v.data(), v.size() * 3 * sizeof(double)); //GL_DYNAMIC_DRAW
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_floor), vertices_floor);
		VertexBufferLayout layout_c;
		layout_c.Push<double>(3); // offsetof(Vertex, Positions);
		//layout_f.Push<float>(3);
		//layout_c.Push<float>(2);
		va_c.AddBuffer(vb_c, layout_c);
		va_c.Unbind();
		vb_c.Unbind();

	}

	void SceneCurves::onImGuiRender()
	{
		

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
		{
			if (ImGui::BeginTabItem("Circle"))
			{
				ImGui::Text("This is the Circle tab!\nnew?");
				
					static float f0 = 0.001f;
					ImGui::InputFloat("input R", &f0, 0.01f, 1.0f, "%.3f");
					
					/*static double d0 = 999999.00000001;
					ImGui::InputDouble("input double", &d0, 0.01f, 1.0f, "%.8f");
					*/
					if (ImGui::Button("add Circle"))
					{
						Geometric_curves_3D* circle = new Circle(f0);
						AddCurves(circle); // DEAD!!!
						double step = 1;
						
						
						std::cout << " NEW CIRCLE!" << std::endl;
				
						
						for (double t = 0; t < (360); t += step) {
							v.push_back(circle->get_point3D(t));

						};
					}
					SceneCurves::onUpdate();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Broccoli"))
			{
				ImGui::Text("This is the Broccoli tab!\nblah blah blah blah blah");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Cucumber"))
			{
				ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		};
		SceneCurves::onRender();
	}

	Geometric_curves_3D*  SceneCurves::AddCurves(Geometric_curves_3D* circle)
	{
		//std::vector<double> number;
		//curves.push_back(std::make_pair(circle, number));
		curves.push_back(circle);
		return 0;
	}

}