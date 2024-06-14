#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>

// Function Prototypes
void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int Physics();
int Initialize();
int Update();
int Render();

// Error callback function
void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s", description);
}

// Key callback function
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Placeholder for key callback logic
}

// Physics update function
int Physics()
{
    // Placeholder for physics update logic
    return 0;
}

// Initialization function
int Initialize()
{
    // Placeholder for initialization logic
    return 0;
}

// Update function
int Update()
{
    // Placeholder for update logic
    return 0;
}

// Render function
int Render()
{
    // Clear the window with the sky blue color
    glClearColor(0.0f, 0.117f, 0.392f, 1.0f); // Sky blue color (R:0, G:30, B:100)
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialize the GLFW library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    // Call the Initialize function
    Initialize();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Call the Physics function
        Physics();

        // Call the Update function
        Update();

        // Call the Render function
        Render();

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}