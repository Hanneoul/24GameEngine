#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

struct Vertex
{
	float x;
	float y;
};

struct Vector
{
	float x_meter;
	float y_meter;
};

int MoveVertex(Vertex point, Vector meter)
{
	return 0;
}

int RotateVertex(Vertex point, float angle_degree)
{
	return 0;
}

int ScaleVertex(Vertex point, Vector meter)
{
	return 0;
}


float angle = 0;

int Initialize()
{
	return 0;
}

int Update()
{
	return 0;
}

int Render()
{
	return 0;
}


int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(800, 800, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	Initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Update();
		Render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}