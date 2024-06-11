#pragma once
#if 1

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


	struct Vertex {
		// position
		glm::vec3 Position;
		// color
		//glm::vec3 Color;
		// texCoords
		glm::vec2 TexCoords;
	};
	using scene::Vertex;
	
	//float a = 1, b = 1, h = 0.2;
	static std::array<Vertex, 8> CreateFloor(float x, float y)
	{
		float size = 1, h = 0.2;
		

		Vertex v0;
		v0.Position = { x, y, -0.5f * h };
		v0.TexCoords = { 0, 0 };

		Vertex v1;
		v1.Position = { x + size, y, -0.5f * h };
		v1.TexCoords = { 0, 0 };

		Vertex v2;
		v2.Position = { x + size,  y + size, -0.5f * h };
		v2.TexCoords = { 0, 0 };

		Vertex v3;
		v3.Position = { x,  y + size, -0.5f * h };
		v3.TexCoords = { 0, 0 };
		//___________
		Vertex v4;
		v4.Position = { x, y, 0.0f * h };
		v4.TexCoords = { 0, 0 };

		Vertex v5;
		v5.Position = { x + size, y, 0.0f * h };
		v5.TexCoords = { 1, 0 };

		Vertex v6;
		v6.Position = { x + size,  y + size,  0.0f };
		v6.TexCoords = { 1, 1 };

		Vertex v7;
		v7.Position = { x,  y + size,  0.0f };
		v7.TexCoords = { 0, 1 };

		/////////////////
		Vertex v8;
		v8.Position = { 0.5f,  0.5f,  0.0f };
		v8.TexCoords = { 0, 0 };

		Vertex v9;
		v9.Position = { 0.5f,  0.5f,  0.0f };
		v9.TexCoords = { 0, 0 };

		Vertex v10;
		v10.Position = { -0.5f,  0.5f,  0.0f };
		v10.TexCoords = {};

		Vertex v11;
		v11.Position = { -0.5f, -0.5f,  0.0f };
		v11.TexCoords = {};

		Vertex v12;
		v12.Position = { -0.5f,  0.5f,  0.0f };
		v12.TexCoords = {};

		Vertex v13;
		v13.Position = { -0.5f,  0.5f, -0.5f * h };
		v13.TexCoords = {};

		Vertex v14;
		v14.Position = { -0.5f, -0.5f, -0.5f * h };
		v14.TexCoords = {};

		Vertex v15;
		v15.Position = { -0.5f, -0.5f, -0.5f * h };
		v15.TexCoords = {};

		return { v0, v1, v2, v3, v4, v5, v6, v7 };


	}
	
	/*/float  vertices_floor[] = {
	-0.5f, -0.5f, -0.5f * h,  0.0f, 0.0f,	//0
	 0.5f, -0.5f, -0.5f * h,  1.0f, 0.0f,	//1	
	 0.5f,  0.5f, -0.5f * h,  1.0f, 1.0f,	//2
	 0.5f,  0.5f, -0.5f * h,  1.0f, 1.0f,	//2
	-0.5f,  0.5f, -0.5f * h,  0.0f, 1.0f,	//3
	-0.5f, -0.5f, -0.5f * h,  0.0f, 0.0f,	//0

	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,	//
	 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.0f,  1.0f, 0.0f,	//0
	-0.5f,  0.5f, -0.5f * h,  1.0f, 1.0f,	//1
	-0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,	//2
	-0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,	//2
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,	//3
	-0.5f,  0.5f,  0.0f,  1.0f, 0.0f,	//0

	 0.5f,  0.5f,  0.0f,  1.0f, 0.0f,	//
	 0.5f,  0.5f, -0.5f * h,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f * h,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f * h,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f * h,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f * h,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f * h,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(3.0f, 0.0f, 0.0f),

		glm::vec3(0.0f, 1.0f,	0.0f),
		glm::vec3(1.0f, 1.0f,	0.0f),
		glm::vec3(2.0f,	1.0f,	0.0f),
		glm::vec3(3.0f,	1.0f,	0.0f),

		glm::vec3(0.0f,  2.0f,  0.0f),
		glm::vec3(1.0f,  2.0f,	0.0f),
		glm::vec3(2.0f,	2.0f,	0.0f),
		glm::vec3(3.0f,	2.0f,	0.0f),

		glm::vec3(0.0f, 3.0f,	0.0f),
		glm::vec3(1.0f, 3.0f,	0.0f),
		glm::vec3(2.0f,	3.0f,	0.0f),
		glm::vec3(3.0f,	3.0f,	0.0f),

	};
	/*
	float vertices_floor[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//0
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	//1
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//2
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//3

			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,	//0
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,	//1
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,	//2
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,	//3

	};

	unsigned int indices_floor[] = {
		0, 1, 2, 3,
		7, 6, 5, 4,
		0, 1, 5, 4,
		3, 0, 4, 7,
		2, 3, 7, 6,
		1, 2, 6, 5
	};*/

	/*

	GLfloat vertices_floor2222[] = {
		// positions        // colors
		// for +Z (cube front)
		-0.5f * a, 0.5f * b, 0.5f * h, 0.0f, 0.0f, 0.0f,  // top left (-X, +Y)
		0.5f * a, 0.5f * b, 0.5f * h, 0.0f, 1.0f, 0.0f,   // top right (+X, +Y)
		0.5f * a, -0.5f * b, 0.5f * h, 1.0f, 0.0f, 0.0f,  // bottom right (+X, -Y)
		-0.5f * a, -0.5f * b, 0.5f * h, 1.0f, 1.0f, 0.0f, // bottom left (-X, -Y)

		// for -Z (cube back)
		-0.5f * a, 0.5f * b, -0.5f * h, 1.0f, 1.0f, 0.0f,  // top left (-X, +Y)
		0.5f * a, 0.5f * b, -0.5f * h, 1.0f, 0.0f, 0.0f,   // top right (+X, +Y)
		0.5f * a, -0.5f * b, -0.5f * h, 0.0f, 1.0f, 0.0f,  // bottom right (+X, -Y)
		-0.5f * a, -0.5f * b, -0.5f * h, 0.0f, 0.0f, 0.0f, // bottom left (-X, -Y)
	};
	GLfloat vertices_floor111[] = {
		// positions        // colors
		// for +Z (cube front)
		-0.5f * a, 0.5f * b, 0.5f * h, 0.0f, 0.0f, 0.0f,  // top left (-X, +Y)
		-0.5f * a, -0.5f * b, 0.5f * h, 1.0f, 1.0f, 0.0f, // bottom left (-X, -Y)
		0.5f * a, -0.5f * b, 0.5f * h, 1.0f, 0.0f, 0.0f,  // bottom right (+X, -Y)
		0.5f * a, 0.5f * b, 0.5f * h, 0.0f, 1.0f, 0.0f,   // top right (+X, +Y)



		// for -Z (cube back)
		-0.5f * a, 0.5f * b, -0.5f * h, 1.0f, 1.0f, 0.0f,  // top left (-X, +Y)
		0.5f * a, 0.5f * b, -0.5f * h, 1.0f, 0.0f, 0.0f,   // top right (+X, +Y)
		0.5f * a, -0.5f * b, -0.5f * h, 0.0f, 1.0f, 0.0f,  // bottom right (+X, -Y)
		-0.5f * a, -0.5f * b, -0.5f * h, 0.0f, 0.0f, 0.0f, // bottom left (-X, -Y)
	};
	GLuint indices_floor[] = {
		// clang-format off
		// those indices better to be in cube order
		// quads
		0, 3, 2,
		0, 1, 2,
		// clang-format on
	};
	// cube sides to render
	GLuint indices_floor2222[] = {
		// clang-format off
		// those indices better to be in cube order
		// quads
		0, 3, 2, 1,
		4, 7, 3, 0,
		1, 2, 6, 5,
		4, 0, 1, 5,
		3, 7, 6, 2,
		5, 6, 7, 4,
		// clang-format on
	};


	*/

	class SceneTest : public Scene 
	{
	public:
		SceneTest();
		~SceneTest();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

	private:
		unsigned int indices_[36]{
				0, 1, 2, 2, 3, 0,
				////////////////
				4, 5, 6, 6, 7, 4,
				////////////////
				0, 4, 7, 7, 3, 0,
				////////////////
				0, 1, 5, 5, 4, 0,
				////////////////
				2, 3, 7, 7, 6, 2,
				////////////////
				1, 2, 6, 6, 5, 1
		};
		VertexArray va_f;
		VertexBuffer vb_f;
		VertexBufferLayout layout_f;
		IndexBuffer* ib_f = new IndexBuffer(indices_, 36);
		//Shader& ourShader;
		float x = 0, y = 0, n = 1;
		Shader* sceneShader;
		int texture;
		unsigned int modelLoc;
		unsigned int viewLoc;
		unsigned int projectionLoc;
		

	};


	class SceneCurves : public Scene
	{
	public:
		SceneCurves();
		~SceneCurves();

		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGuiRender() override;

		void AddCurves(Geometric_curves_3D* curv, double step = 1, double deg = 360);


		int pointSize = 4; // !!!!!!!!!!!!!!!!!!!!!!1

	private:
		//std::vector<std::pair<Geometric_curves_3D*, std::vector<point3D>* > > curves;
		std::vector<Geometric_curves_3D*> curves;
		std::vector<point3D> v;
		


		//   UNIC POINTER!!!!!!!!!!!!!!!!!!!!!
		VertexArray va_c;
		VertexBufferLayout layout_c;
		VertexBuffer vb_c;
		//		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	};

}

#endif