#include <iostream>
#include <GLFW/glfw3.h>
#include "include/box2d/box2d.h"
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

string key_action = "reset";
double scroll_scale = 0.0;
vector<double> render_offset(2,0.0);

void error_callback(int error, const char* description)
{
    cout<<"GLFW Error "<<error<<": "<<description<<endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        key_action = "pause";
    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        key_action = "reset";
    else if (key == GLFW_KEY_LEFT)
        render_offset[0] -= 0.5;
    else if (key == GLFW_KEY_RIGHT)
        render_offset[0] += 0.5;
    else if (key == GLFW_KEY_UP)
        render_offset[1] += 0.5;
    else if (key == GLFW_KEY_DOWN)
        render_offset[1] -= 0.5;

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_scale = yoffset*2.5;
}

int draw(vector<float> &PenA_StartVec, vector<float> &PenB_StartVec)
{

    GLFWwindow* window;

    /* Program-Controlled Variables */

    int width = 960;
    int height = 720;

    double program_time = -1.0; //This time value is how long the program has been running
    double previous_time = -1.0;
    double time_delta = -1.0; //This will be used in the physics "time step"
    double t = 0.0; // This will link the x and y values to a time value

    int velocityIterations = 6;
    int positionIterations = 2;
    
    vector<double> PenA_Render(2,-1);
    vector<double> PenB_Render(2,-1);
    vector<double> center_render(2,-1);

    ofstream data_csv;

    /* User-Controlled Variables */

    bool is_sim_paused = true;

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
    b2Vec2 gravity(0.0f, -9.8f);
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
    PenShape.m_radius= 0.25f;

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

        center_render[0] = (center_pos.x+render_offset[0])
        * scale_factor / width;
        center_render[1] = (center_pos.y+render_offset[1])
         * scale_factor / height;

        PenA_Render[0] = (PenA_Pos.x+render_offset[0])
         * scale_factor / width;
        PenA_Render[1] = (PenA_Pos.y+render_offset[1])
         * scale_factor / height;

        PenB_Render[0] = (PenB_Pos.x+render_offset[0])
         * scale_factor / width;
        PenB_Render[1] = (PenB_Pos.y+render_offset[1])
         * scale_factor / height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        glPointSize(0.25*scale_factor);
        glLineWidth(0.08*scale_factor);
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
            if (t == 0)
                data_csv<<"t,x1,y1,x2,y2\n";
            data_csv<<t<<','<<PenA_Pos.x<<','<<PenA_Pos.y
            <<','<<PenB_Pos.x<<','<<PenB_Pos.y<<'\n';

            world.Step(time_delta, velocityIterations, positionIterations);
            t += time_delta;
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
            t = 0.0;

            data_csv.close();
            data_csv.open("data.csv", ios::out | ios::trunc);
        }
        key_action = "";
        scale_factor += scroll_scale;
        if (scale_factor < 0)
            scale_factor = 0;
        scroll_scale = 0.0;



    }

    glfwTerminate();
    data_csv.close();

    return 0;

}

int main(int argc, char *argv[])
{


    int draw_return = 0;
    vector<float> PenA_StartVec(2,0);
    vector<float> PenB_StartVec(2,0);
    
    cout<<"<Enter>: Reset"<<endl<<"<Space>: Pause"<<endl;
    cout<<"<Scroll>: Zoom In/Out"<<endl;
    cout<<"<Left Arrow>: Move Left"<<endl<<"<Right Arrow>: Move Right"<<endl;
    cout<<"<Up Arrow>: Move Up"<<endl<<"<Down Arrow>: Move Down"<<endl;
    cout<<"<Escape>: Exit"<<endl<<endl;
    
    if (argc == 5)
    {
        PenA_StartVec[0] = stof(argv[1]);
        PenA_StartVec[1] = stof(argv[2]);

        PenB_StartVec[0] = stof(argv[3]);
        PenB_StartVec[1] = stof(argv[4]);
    }
    else
    {
        PenA_StartVec[0] = 5.0f;
        PenA_StartVec[1] = 0.0f;

        PenB_StartVec[0] = 10.0f;
        PenB_StartVec[1] = 0.0f;

        cout<<"Tip: If you want to define your own starting point,"<<endl
        <<"run this program from terminal with 4 arguments"<<endl
        <<"with the coordinates you want to start from."<<endl<<endl;

        cout<<"Example: ./DoublePendulum 1.2 3.4 5.6 7.8"<<endl<<endl;

        cout<<"This will set the first pendulum's starting point"<<endl
        <<"to (1.2, 3.4), and it will set the second pendulum's"<<endl
        <<"starting point to (5.6, 7.8)."<<endl<<endl;
    }
    
    draw_return = draw(PenA_StartVec, PenB_StartVec);

    return draw_return;

}