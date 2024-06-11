#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <memory>
#include <filesystem>

//#include "../external/3D_curves/3D_curves.h"
#include "3D_curves/3D_curves.h"
#include "Renderer/ShaderProgram.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "Renderer/stb_image.h"
#include "camera.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Model.h"
#include "Scene/Scene.h"
#include "Scene/SceneTest.h"
#include "Scene/SceneTexture.h"


//frag_color = vec4(color);

Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}
double lastX; // = SCR_WIDTH / 2.0;
double lastY; // = SCR_HEIGHT / 2.0;
//bool firstMouse = true;
bool LeftPress; // = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
bool LineMode = true;

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



/*
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -1
	5.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};*/

/*struct Vertex {
	// position
	glm::vec3 Position;
	// color
	//glm::vec3 Color;
	// texCoords
	glm::vec2 TexCoords;
};*/


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
	// settings
	extern const unsigned int SCR_WIDTH; // = 800;
	extern const unsigned int SCR_HEIGHT; // = 600;
	

	// camera
	//Camera camera(glm::vec3(30.0f, 30.0f, 30.0f));
	extern Camera camera;


	// glfw: initialize and configure
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// if(glewInit() != GLEW_OK)     ????????glad?
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}
	std::cout << "OpenGL " << GLVersion.major <<"."<<GLVersion.minor << std::endl;
	glClearColor(0, 0, 0, 1);


	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		std::cout << "DEBUG!\n";
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	


	//Shader ourShader("C:/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.vs", 
		//					"/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.frag");
	//Shader ourShader("./Shader/shader.vs", "./Shader/shader.frag");
	
	/*
	// Texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width = 0, height = 0, nrChannels = 0;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	unsigned char* image = stbi_load(".\\Shader\\main_floor.jpg", &width, &height, &nrChannels, 0);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "load texture: OK!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Texture2
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	width = 0; height = 0; nrChannels = 0;
	stbi_set_flip_vertically_on_load(true);
	image = stbi_load(".\\Shader\\second_floor.jpg", &width, &height, &nrChannels, 4);
	if (image)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "load texture: OK!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, texture);

	*/

	

	
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
	//stbi_set_flip_vertically_on_load(false);
	
	/*
	// configure global opengl state-----------------------------
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_LINE GL_FILL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glPointSize(4);
	//glLineWidth(1);
	*/
	
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
	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
	
	

	scene::Scene* currentScene = nullptr;
	scene::SceneMenu* sceneMenu = new scene::SceneMenu(currentScene);
	currentScene = sceneMenu;
	//scene::SceneTest sceneTest();
	//SceneTextureSimple

	sceneMenu->RegScene<scene::SceneTest>("Scene Test");
	sceneMenu->RegScene<scene::SceneCurves>("SceneCurves"); 
	sceneMenu->RegScene<scene::SceneTexture>("SceneTexture");
	sceneMenu->RegScene<scene::SceneTextureSimple>("SceneTextureSimple");
	
	
		
		//Model ourModel(".\\Shader\\backpack\\backpack.obj");
		Model ourModel(".\\Shader\\ibm\\ibm_1401.obj");
		bool modelOnRender = false;
		bool XYZ = true;

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
			glfwPollEvents();
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

/*
			ourShader.use();

			// retrieve the matrix uniform locations
			unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
			unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
			
			glm::mat4 projection;
			glm::mat4 view;
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// camera/view transformations
			view = camera.GetViewMatrix();
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);



			glm::mat4 model = glm::mat4(1.0f);
			
			if (XYZ)
			{
				glm::vec4 color_v(1.0f, 0.0f, 0.0f, 1.0f);
				//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
				model = glm::scale(model, glm::vec3(10 * XYZ_scale, 10 * XYZ_scale, 10 * XYZ_scale));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				//XYZ
				color_v = { 1.0f, 0.0f, 0.0f, 1.0f };
				glUniform4fv(glGetUniformLocation(ourShader.ID, "color"), 1, &color_v[0]);
				OX.draw();
				color_v = { 0.0f, 1.0f, 0.0f, 1.0f };
				glUniform4fv(glGetUniformLocation(ourShader.ID, "color"), 1, &color_v[0]);
				OY.draw();
				color_v = { 0.0f, 0.0f, 1.0f, 1.0f };
				glUniform4fv(glGetUniformLocation(ourShader.ID, "color"), 1, &color_v[0]);
				OZ.draw();
			}
	

			if (modelOnRender) 
			{

				// render the loaded model
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
				model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
				ourShader.setMat4("model", model);
				ourModel.Draw(ourShader);

			}


		
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);
			ImGui::Checkbox("model", &modelOnRender);
			ImGui::Checkbox("XYZ", &XYZ);

			//ImGui::SliderFloat("floatX", &x, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::SliderFloat("floatY", &y, 0.0f, 5.0f);
			//ImGui::SliderInt("Number", )
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			/*if (ImGui::Button("Button +"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				n++;
			if (ImGui::Button("Button -"))
				n--;
			ImGui::SameLine();
			ImGui::Text("counter = %i", n);
		*//*

			if (ImGui::Button("FORWARD -"))
				camera.ProcessKeyboard(FORWARD, deltaTime);
			if (ImGui::Button("BACKWARD -"))
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			if (ImGui::Button("LEFT -"))
				camera.ProcessKeyboard(LEFT, deltaTime);
			if (ImGui::Button("RIGHT -"))
				camera.ProcessKeyboard(RIGHT, deltaTime);
			

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		
			
			ImGui::End();
		}
		*/
		ImGui::Begin("Test");
		
		if (currentScene != sceneMenu && ImGui::Button("<-"))
		{
			delete currentScene;
			currentScene = sceneMenu;
			
		};
		currentScene->onRender();
		currentScene->onUpdate(0.0f);
		currentScene->onImGuiRender();
		
		//ImGui::ShowDemoWindow();
		ImGui::End();
	

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
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		/*float xoffset = xpos - lastX; 
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		*/
		if (LeftPress == GLFW_PRESS)
		{
			//float xoffset = xpos - lastX;
			//float yoffset = lastY - ypos;
			float xoffset = lastX - xpos;
			float yoffset = ypos - lastY;
			camera.ProcessMouseMovement(xoffset, yoffset);
		}
		lastX = xpos;
		lastY = ypos;

		

	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		LeftPress = GLFW_PRESS;
		glfwGetCursorPos(window, &lastX, &lastY);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		LeftPress = GLFW_RELEASE;
}



