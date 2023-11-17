#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <memory>

#include "../external/3D_curves/3D_curves.h"
#include "Renderer/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/stb_image.h"
#include "camera.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
/*
#include "imgui/"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
*/

#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_glfw.h"
#include "../external/imgui/imgui_impl_opengl3.h"
//#include "Model.h"

//frag_color = vec4(color);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool LineMode = true;

// camera
Camera camera(glm::vec3(30.0f, 30.0f, 30.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//  settings XYZ
int XYZ_scale = 1;

float  vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	//1	
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//2
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	//3
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	//0

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//0
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	//1
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//2
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	//2
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//3
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//0

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	//
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


float a = 1, b = 1, h = 0.2;

/*
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};*/

struct Vertex {
	// position
	glm::vec3 Position;
	// color
	//glm::vec3 Color;
	// texCoords
	glm::vec2 TexCoords;
};

static std::array<Vertex, 8> CreateFloor(float x, float y)
{
	float size = 1;

	Vertex v0;
	v0.Position = { x, y, -0.5f * h };
	v0.TexCoords = {};

	Vertex v1;
	v1.Position = { x + size, y, -0.5f * h };
	v1.TexCoords = {};

	Vertex v2;
	v2.Position = { x + size,  y + size, -0.5f * h };
	v2.TexCoords = {};

	Vertex v3;
	v3.Position = { x,  y + size, -0.5f * h };
	v3.TexCoords = {};
	//___________
	Vertex v4;
	v4.Position = { x, y, 0.0f * h };
	v4.TexCoords = {};

	Vertex v5;
	v5.Position = { x + size, y, 0.0f * h };
	v5.TexCoords = {};

	Vertex v6;
	v6.Position = { x + size,  y + size,  0.0f };
	v6.TexCoords = {};

	Vertex v7;
	v7.Position = { x,  y + size,  0.0f };
	v7.TexCoords = {};

	Vertex v8;
	v8.Position = { 0.5f,  0.5f,  0.0f };
	v8.TexCoords = {};

	Vertex v9;
	v9.Position = { 0.5f,  0.5f,  0.0f };
	v9.TexCoords = {};

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
float  vertices_floor[] = {
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


class Line {
	unsigned int VBO, VAO;
	std::vector<float> vertices;
	glm::vec3 startPoint;
	glm::vec3 endPoint;
public:
	Line(glm::vec3 start, glm::vec3 end) {

		startPoint = start;
		endPoint = end;

		vertices = {
			 start.x, start.y, start.z,
			 end.x, end.y, end.z,

		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	int draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 2);
		return 1;
	}

	~Line() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};



int main(void)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL01", NULL, NULL);
	if (window == NULL)
    {
		std::cout << " glfwCreateWindow ERROR" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// if(glewInit() != GLEW_OK)     ????????glad?

	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}
	std::cout << "OpenGL " << GLVersion.major <<"."<<GLVersion.minor << std::endl;
	glClearColor(0, 0, 0, 1);
	

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	//Shader ourShader("C:/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.vs", 
		//					"/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.frag");
	Shader ourShader(".\\Shader\\shader.vs", ".\\Shader\\shader.frag");
	
	

	
	VertexArray va_f;
	VertexBuffer vb_f(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);
	VertexBufferLayout layout_f;
	layout_f.Push<float>(3); // offsetof(Vertex, Positions);
	//layout_f.Push<float>(3);
	layout_f.Push<float>(2);
	va_f.AddBuffer(vb_f, layout_f);
	//IndexBuffer ib_f(indices_floor, 6);
	//ib_f.Unbind();

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

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //GL_LINE GL_FILL
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(4);
	//glLineWidth(1);

	
	glm::vec3 start(-1.0f, 0.0f, 0.0f);
	glm::vec3 end = { 1.0f, 0.0f, 0.0f };
	Line OX(start, end);
	start = { 0.0f, -1.0f, 0.0f };
	end = { 0.0f,  1.0f, 0.0f };
	Line OY(start, end);
	start = { 0.0f,  0.0f, -1.0f };
	end = { 0.0f, -0.0f, 1.0f };
	Line OZ(start, end);


	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	// build and compile shaders
	// -------------------------
	//Shader ourShader(".\\Shader\\shader.vs", ".\\Shader\\shader.frag"); //".\\Shader\\shader.vs"
	
	
	
	// load models
	// -----------
	//Model ourModel(".\\Shader\\backpack\\backpack.obj"); //.\\Shader\\ibm.obj     backpack.obj

	

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
	
	float x = 0, y = 0, n = 1;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ourShader.Use();
			

		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(ourShader.Program, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.Program, "view");
		unsigned int projectionLoc = glGetUniformLocation(ourShader.Program, "projection");
		glm::vec4 color_v(1.0f, 0.0f, 0.0f, 1.0f);
	
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		// camera/view transformations
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		

		
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10 * XYZ_scale, 10 * XYZ_scale, 10 * XYZ_scale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		//XYZ
		color_v = { 1.0f, 0.0f, 0.0f, 1.0f };
		glUniform4fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OX.draw();
		color_v = { 0.0f, 1.0f, 0.0f, 1.0f };
		glUniform4fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OY.draw();
		color_v = { 0.0f, 0.0f, 1.0f, 1.0f };
		glUniform4fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OZ.draw();
		
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
		

		unsigned int indices_[]{
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
		
		auto q = CreateFloor(x, y);
		Vertex vertices_floor[8];
		memcpy(vertices_floor, q.data(), q.size() * sizeof(Vertex));
		va_f.Bind();
		vb_f.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_floor), vertices_floor);
		IndexBuffer ib_f(indices_, 36);
		//ib_f.Bind();
		//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		color_v = { 0.3f, 0.5f, 1.0f, 1.0f };
		glUniform4fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		for (unsigned int i = 0; i < n; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z));
			//float angle = 2.0f * (20 - i);
			//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			//glDrawArrays(GL_TRIANGLES, 0, 8);
			//glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
		};
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		/*		//model render
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ourModel.Draw(ourShader);
		*/

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("floatX", &x, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("floatY", &y, 0.0f, 5.0f);
			//ImGui::SliderInt("Number", )
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				n++;
			ImGui::SameLine();
			ImGui::Text("counter = %i", n);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		//glViewport(0, 0, display_w, display_h);
		//glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		//glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

				
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents(); 
		//glfwWaitEvents(); //Ч лучший выбор, ≈сли вместо этого вам нужно обновить рендеринг только после того, 
		//как вы получили новые входные данные. ќн ждет, пока не будет получено хот€ бы одно событие, тем временем перевод€ поток в сп€щий режим, 
		//а затем обрабатывает все полученные событи€. Ёто экономит много циклов ÷ѕ и полезно, например, дл€ многих видов инструментов редактировани€.
		
    }
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, LineMode ? GL_FILL : GL_LINE);
		if (LineMode) {
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			LineMode = false;
		}
		else {

			glDisable(GL_DEPTH_TEST);
			//glDisable(GL_CULL_FACE);
			LineMode = true;
		}


	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		lastX += 0.01;
		camera.ProcessMouseMovement(lastX, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		lastX += 0.01;
		camera.ProcessMouseMovement(lastX, 0);
	}
}
		

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}




