
#include <GL/glut.h>
#include "render_sides.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>


// glabal variables
char title[] = "Cube";
GLfloat rotationAngle = 15.0f;
int refreshMills = 10;                            // refresh rate
Rendered_cube cube;                               // cube class
GLfloat rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f; // needed to rotated cube itself
GLfloat original_vertex_positions[] = {0.0f, 0.0f, 1.0f, 1.0f};

std::string formate_time(double value){
    if(value<60){
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    }
    else{
        std::stringstream stream;
        stream << int(value/60)<<":"<<std::fixed << std::setprecision(2)<<value-60*int(value/60);
        return stream.str();
    }
}
// OpenGl graphics
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // bg color
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void renderBitmapString(GLfloat x, GLfloat y, GLfloat z, void *font, const char *string)
{
    const char *c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void renderStrokeString(GLfloat x, GLfloat y, GLfloat z, float scale, const std::string s)
{
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);

    for (int c = 0; c < s.size(); c++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[c]);
    }
    glPopMatrix();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();                   // reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -10.0f);   // center cube
    glRotatef(rot_y, 0.0f, 1.0f, 0.0f); // handeling cube rotations (y axis)
    glRotatef(rot_x, 1.0f, 0.0f, 0.0f); // handeling cube rotations (x axis)
    glRotatef(rot_z, 0.0f, 0.0f, 1.0f); // handeling cube rotations (z axis)


    // render sides
    cube.render_front();
    cube.render_top();
    cube.render_bot();
    cube.render_right();
    cube.render_left();
    cube.render_back();

    glLoadIdentity();
    std::chrono::duration<double, std::milli> solving_time;
    if (cube.get_cube().is_solved())
    {
        solving_time = cube.get_cube().end_time - cube.get_cube().start_time;
    }
    else if (cube.get_cube().solving)
    {
        solving_time = std::chrono::steady_clock::now() - cube.get_cube().start_time;
        
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    renderStrokeString(-1.0f, 3.0f, -10.0f, 0.005, formate_time(solving_time.count() / 1000));
    GLfloat modelview_matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

    // Transform original vertex positions
    GLfloat transformed_coords[4]; // Array to store transformed coordinates (homogeneous)
    for (int i = 0; i < 4; i++)
    {
        transformed_coords[i] = 0.0f;
        for (int j = 0; j < 4; j++)
        {
            transformed_coords[i] += modelview_matrix[i * 4 + j] * original_vertex_positions[j];
        }
    }

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

void timer(int value)
{
    glutPostRedisplay();                   // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

// Handler for window re-size event
void reshape(GLsizei width, GLsizei height)
{
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


void scramble(int count)
{
    char moves[] = "qweasdQWEASD";
    srand(time(0));
    int index;
    for (int i = 0; i < count; i++)
    {
        index = rand() % 9;
        cube.turn(moves[index]);
        display();
        usleep(50000);
    }
    cube.get_cube().scramble_state = true;
}

void keyboard_func_wrapper(unsigned char key, int x, int y)
{ // k, i, j, l used to rotate cube, other keys are procesed for layer rotations
    if (key == 'r')
    {
        cube.get_cube().reset();
    }
    else if (key == 'f')
    {
        scramble(60);
    }
    else if (key == 'x')
    {
        scramble(2);
    }
    else if (key == 'k')
    {
        rot_x += 5.0f;
    }
    else if (key == 'i')
    {
        rot_x -= 5.0f;
    }
    else if (key == 'j')
    {
        rot_y -= 5.0f;
    }
    else if (key == 'l')
    {
        rot_y += 5.0f;
    }
    else if (key == 'u')
    {
        rot_z += 5.0f;
    }
    else if (key == 'o')
    {
        rot_z -= 5.0f;
    }
    else
        cube.turn(key);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                    // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(800, 600);                             // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                           // Position the window's initial top-left corner
    glutCreateWindow(title);                                  // Create window with the given title
    glutDisplayFunc(display);                                 // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);                                 // Register callback handler for window re-size event
    glutKeyboardFunc(keyboard_func_wrapper);
    initGL();                                                 // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);                               // First timer call immediately
    glutMainLoop();                                           // Enter the infinite event-processing loop
    return 0;
}
