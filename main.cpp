#include <iostream>
#include <GLFW/glfw3.h>
#include "include/box2d/box2d.h"
#include <vector>
#include <math.h>

using namespace std;

string key_action = "";

void error_callback(int error, const char* description)
{
    cout<<"GLFW Error "<<error<<": "<<description<<endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        key_action = "pause";
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        key_action = "reset";
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int draw()
{

    GLFWwindow* window;

    /* Program-Controlled Variables */

    int width = 1280;
    int height = 720;

    double ratio = 1280/720;
    double program_time = -1.0; //This time value is how long the program has been running
    double previous_time = -1.0;
    double time_delta = -1.0; //This will be used in the physics "time step"

    int velocityIterations = 6;
    int positionIterations = 2;
    
    vector<double> PenA_Render(2,-1);
    vector<double> PenB_Render(2,-1);
    vector<double> center_render(2,-1);

    /* User-Controlled Variables */

    bool is_sim_paused = true;

    vector<float> PenA_StartVec(2,0);
    vector<float> PenB_StartVec(2,0);

    PenA_StartVec[0] = 5.0f;
    PenA_StartVec[1] = 0.0f;

    PenB_StartVec[0] = 10.0f;
    PenB_StartVec[1] = 0.0f;

    double scale_factor = 50;

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
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(1);

    /* Initialize Physics */
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    b2BodyDef centerDef;
    centerDef.position.Set(0.0f, 0.0f);
    b2Body* center = world.CreateBody(&centerDef);

    b2BodyDef PenA_Def;
    PenA_Def.type = b2_dynamicBody;
    PenA_Def.position.Set(PenA_StartVec[0], PenA_StartVec[1]);
    b2Body* PenA = world.CreateBody(&PenA_Def);

    b2BodyDef PenB_Def;
    PenB_Def.type = b2_dynamicBody;
    PenB_Def.position.Set(PenB_StartVec[0],PenB_StartVec[1]);
    b2Body* PenB = world.CreateBody(&PenB_Def);

    b2CircleShape PenShape;
    PenShape.m_radius= 0.5f;

    b2FixtureDef PenFixtureDef;
    PenFixtureDef.shape = &PenShape;
    PenFixtureDef.density = 1.0f;
    PenFixtureDef.friction = 0.0f;
    PenFixtureDef.restitution = 1.0f;

    PenA->CreateFixture(&PenFixtureDef);
    PenB->CreateFixture(&PenFixtureDef);

    b2RevoluteJointDef JointADef;
    JointADef.bodyA = center;
    JointADef.bodyB = PenA;
    JointADef.collideConnected = false;
    JointADef.localAnchorA.Set(0,0);
    JointADef.localAnchorB.Set(
        0 - PenA_StartVec[0],
        0 - PenA_StartVec[1]
    );
    b2Joint* JointA = (b2RevoluteJoint*)world.CreateJoint(&JointADef);
    
    b2RevoluteJointDef JointBDef;
    JointBDef.bodyA = PenA;
    JointBDef.bodyB = PenB;
    JointBDef.collideConnected = false;
    JointBDef.localAnchorA.Set(0,0);
    JointBDef.localAnchorB.Set(
        (0 - PenB_StartVec[0]) + PenA_StartVec[0],
        0 - PenB_StartVec[1] + PenA_StartVec[1]
    );
    b2Joint* JointB = (b2RevoluteJoint*)world.CreateJoint(&JointBDef);
    
   
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        
        /* Run calculations */
        previous_time = program_time;
        program_time = glfwGetTime();
        time_delta = program_time - previous_time;
        
        /* Render here */
        b2Vec2 center_pos = center->GetPosition();
        b2Vec2 PenA_Pos = PenA->GetPosition();
        b2Vec2 PenB_Pos = PenB->GetPosition();

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width/height;

        center_render[0] = center_pos.x * scale_factor / width;
        center_render[1] = center_pos.y * scale_factor / height;

        PenA_Render[0] = PenA_Pos.x * scale_factor / width;
        PenA_Render[1] = PenA_Pos.y * scale_factor / height;

        PenB_Render[0] = PenB_Pos.x * scale_factor / width;
        PenB_Render[1] = PenB_Pos.y * scale_factor / height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glPointSize(10.0f);

        glColor3d(1.0,0.0,0.0);

        glBegin(GL_POINTS);
            glVertex2f(center_render[0],center_render[1]);
            glVertex2f(PenA_Render[0], PenA_Render[1]);
            glVertex2f(PenB_Render[0], PenB_Render[1]);
        glEnd();

        glBegin(GL_LINE_STRIP);
            glVertex2f(center_render[0],center_render[1]);
            glVertex2f(PenA_Render[0], PenA_Render[1]);
            glVertex2f(PenB_Render[0], PenB_Render[1]);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Run physics */
        if (!is_sim_paused)
        {
            world.Step(time_delta, velocityIterations, positionIterations);
        }

        /* Poll for and process events */
        glfwPollEvents();
        if (key_action == "pause")
        {
            is_sim_paused = !is_sim_paused;
        }
        if (key_action == "reset")
        {
            PenA->SetTransform(b2Vec2(PenA_StartVec[0],
            PenA_StartVec[1]),0.0f);
            PenA->SetLinearVelocity(b2Vec2(0,0));

            PenB->SetTransform(b2Vec2(PenB_StartVec[0],
            PenB_StartVec[1]),0.0f);
            PenB->SetLinearVelocity(b2Vec2(0,0));

            is_sim_paused = true;
        }
        key_action = "";



    }

    glfwTerminate();

    return 0;

}

int main()
{

    int draw_return = 0;
    cout<<"<Enter>: Reset"<<endl<<"<Space>: Pause"<<endl;

    draw_return = draw();

    return draw_return;

}