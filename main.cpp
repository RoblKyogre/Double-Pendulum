#include <iostream>
#include <GLFW/glfw3.h>
#include "include/box2d/box2d.h"
#include <vector>

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

int draw(vector<double> &pendulumA, vector<double> &pendulumB)
{

    GLFWwindow* window;

    int width = 1280;
    int height = 720;

    double ratio = 1280/720;
    double program_time = -1.0; //This time value is how long the program has been running
    double previous_time = -1.0;
    double time_delta = -1.0; //This will be used in the physics "time step"

    bool is_sim_running = false;

    /* Initialize GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(width, height, "Double Pendulum", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    /* Initialize Physics */
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        /* Run calculations */
        previous_time = program_time;
        program_time = glfwGetTime();
        time_delta = program_time - previous_time;

        /* Run physics */
        if (is_sim_running)
        {
            cout<<"Physics is running";
        }
        else
        {
            cout<<"Physics is not running";
        }
        
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

    vector<double> pendulumA(2,0); // These will store X and Y coordinates as meters, not pixels
    vector<double> pendulumB(2,0);

    draw_return = draw(pendulumA, pendulumB);

    cout<<"Return Value: "<<draw_return<<endl;
    return draw_return;

}