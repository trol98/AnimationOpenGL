#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Camera.h"

#include <ctime>
#include <iostream>

#include "OpenGLBuffer.h"
#include "OpenGLBufferLayout.h"
#include "OpenGLVertexArray.h"

#include "XMLParser.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, double deltaTime);

void APIENTRY OpenGLMessageCallback(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

constexpr unsigned SCR_WIDTH = 1920;
constexpr unsigned SCR_HEIGHT = 1440;

// camera
Camera camera(glm::vec3(-3.0f, 3.0f, 5.0f));
double lastX = SCR_WIDTH / 2.0;
double lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;

// settings
// use F1, F2, F3
bool flag = false; 

// triangles size = SIZE / VERTEX_COUNT
constexpr unsigned int VERTEX_COUNT = 200;
constexpr float VERTEX_SIZE = 10.0f;




int main()
{
	std::srand(time(nullptr));
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::puts("Failed to initialize GLAD");
		return -1;
	}
	


	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	


	float positions[] = {
	0.0f,  1.0f, 1.0f,
   -1.0f, -1.0f, 0.0f, 
	1.0f, -1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
	};

	//Parser p;

	std::shared_ptr < OpenGLVertexArray> VAO = std::make_shared<OpenGLVertexArray>();
	VAO->Bind();
	OpenGLBufferLayout layout{ {ShaderDataType::Float3, "aPos"} };
	std::shared_ptr<OpenGLVertexBuffer> VBO = std::make_shared<OpenGLVertexBuffer>(positions, 9 * sizeof(float));
	VBO->SetLayout(layout);
	std::shared_ptr <OpenGLIndexBuffer> EBO = std::make_shared<OpenGLIndexBuffer>(indices, 3);
	
	VAO->AddVertexBuffer(VBO);
	VAO->SetIndexBuffer(EBO);

	VAO->Unbind();

	/*
	
	unsigned VBO, EBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,  9 * sizeof(float), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/

	Shader ourShader("AnimationOpenGL/res/shaders/vertex.glsl", "AnimationOpenGL/res/shaders/fragment.glsl");

	XMLNode* node = XMLParser::loadXMLFile("AnimationOpenGL/res/models/cowboy/cowboy.dae");

	for (const auto& elem : *node->get_children())
	{
		std::cout << elem.first << std::endl;
	}
	delete node;
	// configure global opengl state
	// -----------------------------

	ourShader.use();

	// timing
	double deltaTime = 0.0f;
	double lastFrame = 0.0f;
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{	
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		flag = false;

		// input
		// -----
		processInput(window, deltaTime);

		// render
		// ------
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		VAO->Bind();
		glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteVertexArrays(1, &VAO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		flag = true;
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
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX =	xpos;
		lastY =	ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


void APIENTRY OpenGLMessageCallback(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::puts("---------------");
	std::cout << "Debug message (" << id << "): " << message << "\n\n";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::puts("Source: API");				break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::puts("Source: Window System");	break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::puts("Source: Shader Compiler"); break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::puts("Source: Third Party");		break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::puts("Source: Application");		break;
	case GL_DEBUG_SOURCE_OTHER:           std::puts("Source: Other");			break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::puts("Type: Error");					break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::puts("Type: Deprecated Behaviour");	break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::puts("Type: Undefined Behaviour");		break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::puts("Type: Portability");				break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::puts("Type: Performance");				break;
	case GL_DEBUG_TYPE_MARKER:              std::puts("Type: Marker");					break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::puts("Type: Push Group");				break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::puts("Type: Pop Group");				break;
	case GL_DEBUG_TYPE_OTHER:               std::puts("Type: Other");					break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::puts("Severity: high");			break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::puts("Severity: medium");			break;
	case GL_DEBUG_SEVERITY_LOW:          std::puts("Severity: low");			break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::puts("Severity: notification");	break;
	}
	std::puts("");
}