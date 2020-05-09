#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

void error_callback(int error, const char* description)
{
    cout<<"GLFW Error "<<error<<": "<<description<<endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int draw(int width, int height)
{
    GLFWwindow* window;

    /* Set Error Callback */
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Double Pendulum", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set callbacks */
    glfwSetKeyCallback(window, key_callback);

    /* Set Swap Interval */
    glfwSwapInterval(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();
        double ratio;

        /* Render here */
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

int main()
{

    int draw_return = 0;
    
    draw_return = draw(1280, 720);

    cout<<"Return Value: "<<draw_return<<endl;
    return draw_return;
}