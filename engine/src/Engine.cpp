#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine.h"

#include <iostream>

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int InitWindow(int screenWidth, int screenHeight, char* windowTitle) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0; 
}

bool WindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void processInput(GLFWwindow *window)
{
    //if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void BeginDrawing() {
    processInput(window);
}

void EndDrawing() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void ClearBackground(int r, int g, int b, int a) {
    glClearColor((float)r/255, (float)g/255, (float)b/255, (float)a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* GetWindow() {
    return window;
}