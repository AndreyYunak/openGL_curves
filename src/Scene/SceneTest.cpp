#include "SceneTest.h"
#include "../Model.h"

#if 1



namespace scene
{
	

	SceneTest::SceneTest()
	{

		vb_f.VertexBufferData(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);
		layout_f.Push<float>(3); 
		layout_f.Push<float>(2);
		va_f.AddBuffer(vb_f, layout_f);
		sceneShader = new Shader("./Shader/shader1.vs", "./Shader/shader1.frag");
		texture = GL::TextureFromFile("main_floor.jpg", ".\\Shader");
		sceneShader->use();
		sceneShader->setInt("mytexture", 0);
		modelLoc = glGetUniformLocation(sceneShader->ID, "model");
		viewLoc = glGetUniformLocation(sceneShader->ID, "view");
		projectionLoc = glGetUniformLocation(sceneShader->ID, "projection");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		
		//IndexBuffer ib_f(indices_floor, 6);
		//ib_f.Unbind();


		va_f.Unbind();
		vb_f.Unbind();
		/*
		VertexArray va_f;
		VertexBuffer vb_f(vertices_floor, sizeof(vertices_floor), GL_STATIC_DRAW);
		VertexBufferLayout layout_f;
		layout_f.Push<float>(3, 2);
		va_f.AddBuffer(vb_f, layout_f);
		//IndexBuffer ib_f(indices_floor, 6);
		va_f.Unbind();
		//ib_f.Unbind();
		*/
		Circle circ(10);
		std::vector<point3D> v1;
		double step = 10;
		point3D point;

		for (double t = 0; t < (360); t += step) {
			v1.push_back(circ.get_point3D(t));

		};


		std::cout << "v1.size() = " << v1.size() << std::endl
			<< "v1.size() * sizeof(double) = " << v1.size() * sizeof(double) << std::endl
			<< "sizeof(v1) = " << sizeof(v1) << std::endl
			<< "sizeof(v1.data()) = " << sizeof(v1.data()) << std::endl;


		VertexArray va_c;
		VertexBuffer vb_c(v1.data(), v1.size() * 3 * sizeof(double)); //GL_DYNAMIC_DRAW
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_floor), vertices_floor);
		VertexBufferLayout layout_c;
		layout_c.Push<double>(3); // offsetof(Vertex, Positions);
		//layout_f.Push<float>(3);
		//layout_c.Push<float>(2);
		va_c.AddBuffer(vb_c, layout_c);
		va_c.Unbind();
		vb_c.Unbind();

		

		auto q = CreateFloor(x, y);
		Vertex vertices_floor[8];
		memcpy(vertices_floor, q.data(), q.size() * sizeof(Vertex));
		va_f.Bind();
		vb_f.Bind();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_floor), vertices_floor);
		//IndexBuffer ib_f(indices_, 36);
		ib_f->Bind();
		//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//color_v = { 0.3f, 0.5f, 1.0f, 1.0f };

	}

	SceneTest::~SceneTest()
	{
	}

	void SceneTest::onRender()
	{
		// retrieve the matrix uniform locations
		//unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		

		//glUniform4fv(glGetUniformLocation(ourShader.ID, "color"), 1, &color_v[0]);
		/*for (unsigned int i = 0; i < 1; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z));
			//model = glm::translate(model, glm::vec3(v1[i].x, v1[i].y, v1[i].z));

			//float angle = 2.0f * (20 - i);
			//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			//glDrawArrays(GL_TRIANGLES, 0, 8);
			//glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
		};
		*/
		sceneShader->use();

		
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//view = camera.GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10 * XYZ_scale, 10 * XYZ_scale, 10 * XYZ_scale));
		sceneShader->setMat4("model", model);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		va_f.Bind();
		ib_f->Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		/*va_c.Bind();
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_POINTS, 0, v1.size());


		/*
		//CURVES
		color_v = { 1.0f, 1.0f, 1.0f, 1.0f };
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		va.Bind(); //glBindVertexArray(vao_t);
		glDrawArrays(GL_POINTS, 0, n_of_point); //GL_LINE_LOOP
		*/

		/*va_c.Bind();

		for (unsigned int i = 0; i < 16; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(cubePositions[i].x , cubePositions[i].z, cubePositions[i].y));
			//float angle = 2.0f * (20 - i);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		};*/


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
		layout_c.Push<double>(3); // offsetof(Vertex, Positions);
		//layout_f.Push<float>(3);
		//layout_c.Push<float>(2);
	}

	SceneCurves::~SceneCurves()
	{
	}

	void SceneCurves::onRender()
	{
		glEnable(GL_PROGRAM_POINT_SIZE);
		glPointSize(pointSize);
		
	}

	void SceneCurves::onUpdate(float deltaTime = 0)
	{
		va_c.Bind();
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::mat4(1.0f);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_POINTS, 0, v.size());

	}

	void SceneCurves::onImGuiRender()
	{
		ImGui::SliderInt("point Size", &pointSize, 0, 30);
		//ImGui::SameLine(); //HelpMarker("CTRL+click to input value.");

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("Curves", tab_bar_flags))
		{
			
			if (ImGui::BeginTabItem("Circle"))
			{
				ImGui::Text("This is the Circle tab!\nnew?");
				
					static float f0 = 1.0f;
					static double deg = 360.0f;
					static double step = 1;
					ImGui::InputFloat("input R", &f0, 1.0f, 1.0f, "%.3f");
					ImGui::InputDouble("input DEG", &deg, 1.0f, 1.0f, "%.3f");
					ImGui::InputDouble("input Step", &step, 1.0f, 10.0f, "%.3f");

					
					if (ImGui::Button("add Circle"))
					{
						//Geometric_curves_3D* circle = new Circle(f0);
						AddCurves(new Circle(f0), step, deg); // DEAD!!??		
						std::cout << " NEW CIRCLE! " << f0 << " / step:  " << step << std::endl;
										
					}
					
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Ellipse"))
			{
				static double Rx = 1.0f;
				static double Ry = 1.0f;
				static double deg = 360.0f;
				static double step = 1;
				ImGui::InputDouble("input Rx", &Rx, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input Ry", &Ry, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input DEG", &deg, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input Step", &step, 1.0f, 10.0f, "%.3f");
				
				if (ImGui::Button("add Ellipse"))
				{
					//Geometric_curves_3D* circle = new Circle(f0);
					AddCurves(new Ellipse(Rx, Ry), step, deg); // DEAD!!??		
					std::cout << " NEW Ellipse! " << Rx << ", " << Ry <<" / step:  " << step << std::endl;

				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Helix"))
			{
				static double R = 1.0f;
				static double H = 0.01f;
				static double deg = 360.0f;
				static double step = 1;
				ImGui::InputDouble("input R", &R, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input H", &H, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input DEG", &deg, 1.0f, 1.0f, "%.3f");
				ImGui::InputDouble("input Step", &step, 1.0f, 10.0f, "%.3f");
				
				if (ImGui::Button("add Helix"))
				{
					//Geometric_curves_3D* circle = new Circle(f0);
					AddCurves(new Helix(R, H), step, deg); // DEAD!!??		
					std::cout << " NEW Helix! " << R << ", " << H << " / step:  " << step << std::endl;

				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		};
	}

	void SceneCurves::AddCurves(Geometric_curves_3D* curv, double step, double deg)
	{
		//std::vector<double> number;
		//curves.push_back(std::make_pair(circle, number));
		curves.push_back(curv);
		for (double t = 0; t < (deg); t += step) {
			v.push_back(curv->get_point3D(t));

		};
		va_c.Bind();
		vb_c.VertexBufferData(v.data(), v.size() * 3 * sizeof(double)); //GL_DYNAMIC_DRAW
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_floor), vertices_floor);
		
		va_c.AddBuffer(vb_c, layout_c);
		va_c.Unbind();
		vb_c.Unbind();
	}

}
#endif