#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <iostream>
#include <vector>
#include <list>
#include <memory>

#include "../external/3D_curves/3D_curves.h"
#include "Renderer/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/stb_image.h"
#include "camera.h"

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// if(glewInit() != GLEW_OK)     ????????glad?

	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}
	std::cout << "OpenGL " << GLVersion.major <<"."<<GLVersion.minor << std::endl;
	glClearColor(0, 0, 0, 1);
	
	

	Shader ourShader("C:/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.vs", 
							"/Users/Andrey/source/repos/Curves/openGL_curves/src/Renderer/shader.frag");
	std::list<std::shared_ptr<Geometric_curves_3D>> container1;
	std::cout << "ADD type:\n\t 0 - circle\n\t 1 - ellipse\n\t 2 - helix\n 5 - EXIT\n";
	
	int switch_on = -1;
	while (switch_on != 5) {
		std::cout << "Input: ";
		std::cin >> switch_on;
		std::cout << std::endl;
		switch (switch_on)
		{

		case 0: { //Circle
			double R;
			std::cout << "Input R: ";
			std::cin >> R;
			if (container1.empty()) XYZ_scale = R;
			std::cout << std::endl;
			try {
				container1.emplace_back(std::make_shared<Circle>(R));
			}
			catch (const char* error) {
				std::cerr << error << std::endl;
				break;
			};
			break;
		};
		case 1: {
			double Rx, Ry;
			std::cout << "Input Rx: ";
			std::cin >> Rx;
			std::cout << std::endl;
			std::cout << "Input Ry: ";
			std::cin >> Ry;
			if (container1.empty()) XYZ_scale = Rx;
			std::cout << std::endl;
			try {
				container1.emplace_back(std::make_shared<Ellipse>(Rx, Ry));
			}
			catch (const char* error) {
				std::cerr << error << std::endl;
				break;
			};
			break;
		};
		case 2: {
			double R, Step;
			std::cout << "Input R: ";
			std::cin >> R;
			std::cout << std::endl;
			if (container1.empty()) XYZ_scale = R;
			std::cout << "Input Step: ";
			std::cin >> Step;
			std::cout << std::endl;
			try {
				container1.emplace_back(std::make_shared<Helix>(R, Step));
			}
			catch (const char* error) {
				std::cerr << error << std::endl;
				break;
			};
			break;
		};
		default:
			break;
		};
	};


	double step = 1;
	point3D point;
	int n_of_point = 0;
	std::vector<double> container2;
	for(auto it = container1.begin(); it != container1.end(); it++)
	{
		for (double t = 0; t < (360 * 5); t += step) {
			point = (*it)->get_point3D(t);
			container2.push_back(point.x);
			container2.push_back(point.y);
			container2.push_back(point.z);
			n_of_point++;
		};
	};
	
	
	
	GLuint vao_t = 0;
	GLuint VBO_t;
	glGenVertexArrays(1, &vao_t);
	glGenBuffers(1, &VBO_t);
	glBindVertexArray(vao_t);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_t);
	for (auto it = container1.begin(); it != container1.end(); it++)
	{
		glBufferData(GL_ARRAY_BUFFER, container2.size() * sizeof(double), container2.data(), GL_STATIC_DRAW);
	};
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(4);
	glLineWidth(1);

	
	glm::vec3 start(-1.0f, 0.0f, 0.0f);
	glm::vec3 end = { 1.0f, 0.0f, 0.0f };
	Line OX(start, end);
	start = { 0.0f, -1.0f, 0.0f };
	end = { 0.0f,  1.0f, 0.0f };
	Line OY(start, end);
	start = { 0.0f,  0.0f, -1.0f };
	end = { 0.0f, -0.0f, 1.0f };
	Line OZ(start, end);

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
		
		ourShader.Use();
			

		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(ourShader.Program, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.Program, "view");
		unsigned int projectionLoc = glGetUniformLocation(ourShader.Program, "projection");
		glm::vec3 color_v(1.0f, 0.0f, 0.0f);
	
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
		color_v = { 1.0f, 0.0f, 0.0f };
		glUniform3fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OX.draw();
		color_v = { 0.0f, 1.0f, 0.0f };
		glUniform3fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OY.draw();
		color_v = { 0.0f, 0.0f, 1.0f };
		glUniform3fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		OZ.draw();
		
		//CURVES
		color_v = { 1.0f, 1.0f, 1.0f };
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(glGetUniformLocation(ourShader.Program, "color"), 1, &color_v[0]);
		glBindVertexArray(vao_t);
		glDrawArrays(GL_POINTS, 0, n_of_point); //GL_LINE_LOOP
		

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
		
    }

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




