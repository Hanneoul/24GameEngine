#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES // Required for using M_PI with MSVC
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float moveFactor = 0.0f;
float YmoveFactor = 0.0f;
float scaleFactor = 1.0f;
float earthRotationSpeed = 2.0f * M_PI / 10.0f;  // Earth rotation speed: 10 seconds per rotation
float earthOrbitSpeed = 2.0f * M_PI / 60.0f;    // Earth orbit speed: 1 minute per orbit
float moonRotationSpeed = 2.0f * M_PI / 3.0f;   // Moon rotation speed: 3 seconds per rotation
float moonOrbitSpeed = 2.0f * M_PI / 3.0f;     // Moon orbit speed: 3 seconds per orbit

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Your cursor position callback function remains the same.
}

void drawCircle(float x, float y, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * float(i) / float(segments);
        float cx = x + radius * cosf(angle);
        float cy = y + radius * sinf(angle);
        glVertex2f(cx, cy);
    }
    glEnd();
}

int render()
{
    // Draw Sun (Star)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    drawCircle(0.0f, 0.0f, 0.1f, 50);

    // Draw Earth
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    float earthOrbitRadius = 0.5f;
    float earthX = earthOrbitRadius * cosf(moveFactor);
    float earthY = earthOrbitRadius * sinf(moveFactor);
    glPushMatrix();
    glTranslatef(earthX, earthY, 0.0f);
    glRotatef(moveFactor * 180.0f / M_PI, 0.0f, 0.0f, 1.0f); // Earth rotation
    drawCircle(0.0f, 0.0f, 0.05f, 50);
    glPopMatrix();

    // Draw Moon (Around Earth)
    glColor3f(0.7f, 0.7f, 0.7f); // Gray
    float moonOrbitRadius = 0.1f;
    float moonX = earthX + moonOrbitRadius * cosf(YmoveFactor);
    float moonY = earthY + moonOrbitRadius * sinf(YmoveFactor);
    glPushMatrix();
    glTranslatef(moonX, moonY, 0.0f);
    glRotatef(YmoveFactor * 180.0f / M_PI, 0.0f, 0.0f, 1.0f); // Moon rotation
    drawCircle(0.0f, 0.0f, 0.02f, 30);
    glPopMatrix();

    // Update factors for animation
    moveFactor += earthOrbitSpeed;
    YmoveFactor += moonOrbitSpeed;

    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 800, "Solar System", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}