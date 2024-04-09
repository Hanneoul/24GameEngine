#pragma comment(lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;
	
	window = glfwCreateWindow(1280, 768, "HoHoHo HimNae", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}