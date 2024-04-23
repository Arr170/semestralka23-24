#include <GL/glut.h>
#include "cube.hpp"
#include <iostream>

#define WHITE  1.0f, 1.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define GREEN  0.0f, 1.0f, 0.0f
#define BLUE   0.0f, 0.0f, 1.0f
#define RED    1.0f, 0.0f, 0.0f
#define ORANGE 0.8f, 0.3f, 0.0f

#define MARGIN 0.01f
#define STICKER_SIZE 1.0f
// starting coord for green side
#define WGO_ORIGIN_X 0.0f
#define WGO_ORIGIN_Y 0.0f
#define WGO_ORIGIN_Z 0.0f
// staring coord for blue side
#define WBR_ORIGIN_X 3.0f + MARGIN*2
#define WBR_ORIGIN_Y 0.0f
#define WBR_ORIGIN_Z -(3.0f + MARGIN*2)
// starting coord for white side
#define WBO_ORIGIN_X 0.0f
#define WBO_ORIGIN_Y 3.0f + (MARGIN * 2)
#define WBO_ORIGIN_Z -(3.0f + MARGIN * 2)
// starting coord for yellow side
#define YGO_ORIGIN_X 0.0f
#define YGO_ORIGIN_Y 0.0f
#define YGO_ORIGIN_Z 0.0f
// starting coord for red side
#define WGR_ORIGIN_X 3.0f + (MARGIN * 2)
#define WGR_ORIGIN_Y 3.0f + (MARGIN * 2)
#define WGR_ORIGIN_Z 0.0f

class Rendered_cube{
    Cube * cube;
    public:
    Rendered_cube(){
        this->cube = new Cube();
        //std::cout<<this->cube->G_side[1][1]->name<<'\n';
        this->cube->print_cube();
    }
    void render_top();
    void render_bot();
    void render_back();
    void render_front();
    void render_right();
    void render_left();
    void turn(unsigned char key){
        cube->turn_char(key, 1, 1);
    }
};


void color_switch(int color)
{
    //std::cout<<"color code: "<<color<<'\n';
    switch (color)
    {
    case 1:
        glColor3f(WHITE);
        break;
    case 2:
        glColor3f(YELLOW);
        break;
    case 3:
        glColor3f(GREEN);
        break;
    case 4:
        glColor3f(BLUE);
        break;
    case 5:
        glColor3f(RED);
        break;
    case 6:
        glColor3f(ORANGE);
        break;
    default:
        glColor3f(WHITE);
        break;
    }
}

void Rendered_cube::render_front()
{
    
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float x1, y1, x2, y2, symbolX, symbolY;
            //std::cout <<cube->G_side[i][j]->name<<'\n';
            color_switch(cube->G_side[2-i][j]->name);

            x1 = WGO_ORIGIN_X + (MARGIN + STICKER_SIZE) * j;
            y1 = WGO_ORIGIN_Y + (MARGIN + STICKER_SIZE) * i;
            x2 = x1 + STICKER_SIZE;
            y2 = y1 + STICKER_SIZE;

            // Check if this square is one of the squares to rotate
            // bool rotateSquare = false;
            // for (int k = 0; k < 3; k++)
            // {
            //     if (j == rotateIndices[k][0] && i == rotateIndices[k][1])
            //     {
            //         rotateSquare = true;
            //         break;
            //     }
            // }

            // // Apply rotation to the squares to rotate
            // if (rotateSquare)
            // {
            //     glPushMatrix();
            //     // glTranslatef((x1 + x2) / 2.0f, (y1 + y2) / 2.0f, WGO_ORIGIN_Z);
            //     glRotatef(rotationAngle, 3.0f, 0.0f, 0.0f); //
            //     // glTranslatef(-(x1 + x2) / 2.0f, -(y1 + y2) / 2.0f, -WGO_ORIGIN_Z);
            // }

            // Draw the square
            glBegin(GL_QUADS);
            glVertex3f(x1, y1, WGO_ORIGIN_Z); // lt
            glVertex3f(x2, y1, WGO_ORIGIN_Z); // rt
            glVertex3f(x2, y2, WGO_ORIGIN_Z); // rb
            glVertex3f(x1, y2, WGO_ORIGIN_Z); // lb
            

            glEnd();
        }
    }
}

void Rendered_cube::render_back()
{
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float x1, y1, x2, y2, symbolX, symbolY;

            color_switch(cube->B_side[2-i][j]->name);

            x1 = WBR_ORIGIN_X - (MARGIN + STICKER_SIZE) * j;
            y1 = WBR_ORIGIN_Y + (MARGIN + STICKER_SIZE) * i;
            x2 = x1 - STICKER_SIZE;
            y2 = y1 + STICKER_SIZE;

            glBegin(GL_QUADS);
            glVertex3f(x1, y1, WBR_ORIGIN_Z); // lt
            glVertex3f(x2, y1, WBR_ORIGIN_Z); // rt
            glVertex3f(x2, y2, WBR_ORIGIN_Z); // rb
            glVertex3f(x1, y2, WBR_ORIGIN_Z); // lb
            glEnd();
        }
    }
}

void Rendered_cube::render_top()
{
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float x1, z1, x2, z2, symbolX, symbolY;

            color_switch(cube->W_side[i][j]->name);

            x1 = WBO_ORIGIN_X + (MARGIN + STICKER_SIZE) * j;
            z1 = WBO_ORIGIN_Z + (MARGIN + STICKER_SIZE) * i;
            x2 = x1 + STICKER_SIZE;
            z2 = z1 + STICKER_SIZE;

            // Draw the square
            glBegin(GL_QUADS);
            glVertex3f(x1, WBO_ORIGIN_Y, z1); // lt
            glVertex3f(x2, WBO_ORIGIN_Y, z1); // rt
            glVertex3f(x2, WBO_ORIGIN_Y, z2); // rb
            glVertex3f(x1, WBO_ORIGIN_Y, z2); // lb
            glEnd();
        }
    }
}
void Rendered_cube::render_bot()
{
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float x1, z1, x2, z2, symbolX, symbolY;

            color_switch(cube->Y_side[i][j]->name);

            x1 = YGO_ORIGIN_X + (MARGIN + STICKER_SIZE) * j;
            z1 = YGO_ORIGIN_Z - (MARGIN + STICKER_SIZE) * i;
            x2 = x1 + STICKER_SIZE;
            z2 = z1 - STICKER_SIZE;

            // Draw the square
            glBegin(GL_QUADS);
            glVertex3f(x1, YGO_ORIGIN_Y, z1); // lt
            glVertex3f(x2, YGO_ORIGIN_Y, z1); // rt
            glVertex3f(x2, YGO_ORIGIN_Y, z2); // rb
            glVertex3f(x1, YGO_ORIGIN_Y, z2); // lb
            glEnd();
        }
    }
}

void Rendered_cube::render_right()
{
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float y1, z1, y2, z2, symbolX, symbolY;

            color_switch(cube->R_side[i][j]->name);

            y1 = WGR_ORIGIN_X - (MARGIN + STICKER_SIZE) * i;
            z1 = WGR_ORIGIN_Z - (MARGIN + STICKER_SIZE) * j;
            y2 = y1 - STICKER_SIZE;
            z2 = z1 - STICKER_SIZE;

            // Draw the square
            glBegin(GL_QUADS);
            glVertex3f(WGR_ORIGIN_X, y1, z1); // lt
            glVertex3f(WGR_ORIGIN_X, y2, z1); // rt
            glVertex3f(WGR_ORIGIN_X, y2, z2); // rb
            glVertex3f(WGR_ORIGIN_X, y1, z2); // lb
            glEnd();
        }
    }
}

void Rendered_cube::render_left()
{
    for (int j = 0; j < 3; j++)
    { // x coord
        for (int i = 0; i < 3; i++)
        { // y coord
            float y1, z1, y2, z2, symbolX, symbolY;

            color_switch(cube->O_side[2-i][j]->name);

            y1 = WBO_ORIGIN_X + (MARGIN + STICKER_SIZE) * i;
            z1 = WBO_ORIGIN_Z + (MARGIN + STICKER_SIZE) * j;
            y2 = y1 + STICKER_SIZE;
            z2 = z1 + STICKER_SIZE;

            // Draw the square
            glBegin(GL_QUADS);
            glVertex3f(WBO_ORIGIN_X, y1, z1); // lt
            glVertex3f(WBO_ORIGIN_X, y2, z1); // rt
            glVertex3f(WBO_ORIGIN_X, y2, z2); // rb
            glVertex3f(WBO_ORIGIN_X, y1, z2); // lb
            glEnd();
        }
    }
}

