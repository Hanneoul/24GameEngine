//1. 삼각형으로 별을 그리시오
//2. 마우스 좌클릭 후에 드래그해서 드래그한만큼 별을 이동해주세요
//3. 우클릭하고 우측으로 드래그한만큼 확대 좌측으로 드래그한만큼 축소를 해주세요.
//   (별의 중점을 기준으로 확대/축소가 돼야합니다.)

#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

int setVertexRotation(float x, float y, float angle_degree)
{
	glColor3f(0.7f, 0.8f, 0.85f);
	glVertex2f(x*cos(angle_degree)-(y*sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
	return 0;
}

float angle = 0;

int render()
{
	glBegin(GL_TRIANGLES);

	
	setVertexRotation(0.0f, 0.5f, angle);
	
	setVertexRotation(-0.2f, 0.0f, angle);
	
	setVertexRotation(0.0f, -0.5f, angle);
	
	setVertexRotation(0.0f, -0.5f, angle);
	
	setVertexRotation(0.2f, 0.0f, angle);
	
	setVertexRotation(0.0f, 0.5f, angle);


	glEnd();

	angle = angle + 0.1;

	return 0;
}

////점1
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(0.0f * scaleFactor, (1.0f+ moveFactor) * scaleFactor);
////점2
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(0.5f * scaleFactor, (0.0f+ moveFactor) * scaleFactor);
////점3
//glColor3f(1.0f, 1.0f, 1.0f);
//glVertex2f(-0.5f * scaleFactor, (0.0f+ moveFactor) * scaleFactor);


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

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}