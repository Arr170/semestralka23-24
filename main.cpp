/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include "render_sides.hpp"
#include <iostream>
#include <typeinfo>
//#include "cube.hpp"

/* Global variables */
char title[] = "3D Shapes with animation";
GLfloat rotationAngle = 15.0f;
int refreshMills = 10; // refresh interval in milliseconds [NEW]
Rendered_cube cube;
GLfloat rot_x = 0.0f, rot_y = 0.0f; 

/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);              // Set background color to black and opaque
    //glClearDepth(0.5f);                                // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                           // Enable depth testing for z-culling
    glDisable(GL_BLEND);                               // Disable blending
    glDepthFunc(GL_LEQUAL);                            // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                           // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);                         // To operate on model-view matrix

    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                     // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -10.0f); // Move right and into the screen
    glRotatef(rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef(rot_x, 1.0f, 0.0f, 0.0f); 

    glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
    
    // render sides
    cube.render_front();
    cube.render_top();
    cube.render_bot();  
    cube.render_right();
    cube.render_left();
    cube.render_back();

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
    //glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    // Update the rotational angle after each refresh [NEW]
    //rotationAngle = -0.4f;
}

/* Called back when timer expired [NEW] */
void timer(int value)
{
    glutPostRedisplay();                   // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
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
void keyboard_func_wrapper(unsigned char key, int x, int y){
    if(key == 'k'){
        rot_x += 5.0f;
        std::cout<<"y minus"<<rot_y<<"\n";
    }
    else if(key == 'i'){
        rot_x -= 5.0f;
    }
    else if(key == 'j'){
        rot_y += 5.0f;
        std::cout<<"x minus\n";
    }
    else if(key == 'l'){
        rot_y -= 5.0f;
    }
    else
    cube.turn(key);
}
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(640, 480);     // Set the window's initial width & height
    glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);         // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);         // Register callback handler for window re-size event
    glutKeyboardFunc(keyboard_func_wrapper);
    initGL();                         // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);       // First timer call immediately [NEW]
    glutMainLoop();                   // Enter the infinite event-processing loop
   // return 0;
}