#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "cube.hpp"
#include <GL/glut.h>

using namespace std;

// just for fun, should be deleted for final version
// #define WHITE "\033[0m"
// #define BLACK "\033[30m"              /* Black */
// #define RED "\033[31m"                /* Red */
// #define GREEN "\033[32m"              /* Green */
// #define YELLOW "\033[33m"             /* Yellow */
// #define BLUE "\033[34m"               /* Blue */
// #define MAGENTA "\033[35m"            /* Magenta */
// #define CYAN "\033[36m"               /* Cyan */
// #define WHITE "\033[37m"              /* White */
// #define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
// #define BOLDRED "\033[1m\033[31m"     /* Bold Red */
// #define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
// #define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
// #define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
// #define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
// #define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
// #define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

//colors for rendering
#define WHITE 1.0f, 1.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define ORANGE 0.7f, 0.3f, 0.0f

//Color::Color(GLfloat x, GLfloat y, GLfloat z) : r(x), g(y), b(z){}

Sticker::Sticker(int n, GLfloat r, GLfloat g, GLfloat b){
    cout<<"sticker made, name: "<< '\n';
    this->name = n;
    this->color = Color{r,g,b};
    //cout<<this->color.r<<'\n';
    //cout << this->color.g << '\n';
    //cout << this->color.b << '\n';
}



// enum ClockMove
// {
//     R,
//     L,
//     U,
//     D,
//     F,
//     B
// };
// enum CounterClockMove
// {
//     RP,
//     LP,
//     UP,
//     DP,
//     FP,
//     BP
// };


Cube::Cube(){
    cout<<"CUBE EXISTS!!!\n";
    Sticker white(1, WHITE);
    Sticker yellow(2, YELLOW);
    Sticker green(3, GREEN);
    Sticker blue(4, BLUE);
    Sticker red(5, RED);
    Sticker orng(6, ORANGE);
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            this->W_side[i][j] = new Sticker(1, WHITE); // coords [y][x]{{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
            this->Y_side[i][j] = new Sticker(2, YELLOW);
            this->G_side[i][j] = new Sticker(3, GREEN);
            this->B_side[i][j] = new Sticker(4, BLUE);
            this->R_side[i][j] = new Sticker(5, RED);
            this->O_side[i][j] = new Sticker(6, ORANGE);
            // this->W_side[i][j] = &white; // coords [y][x]{{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
            // this->Y_side[i][j] = &yellow;
            // this->G_side[i][j] = &green;
            // this->B_side[i][j] = &blue;
            // this->R_side[i][j] = &red;
            // this->O_side[i][j] = &orng;
        }
    }
    
}
void Cube::rotate_colors(Sticker **one, Sticker **two, Sticker **three, Sticker **four)
{ // one->two, two->three, three->four, four->one
    Sticker *temp = *one;
    *one = *four;
    *four = *three;
    *three = *two;
    *two = temp;
}
void Cube:: rotate_face(Sticker *face[3][3])
{
    rotate_colors(&face[0][0], &face[0][2], &face[2][2], &face[2][0]);
    rotate_colors(&face[0][1], &face[1][2], &face[2][1], &face[1][0]);
}
void Cube:: rotate_face_counter(Sticker *face[3][3])
{
    rotate_colors(&face[2][0], &face[2][2], &face[0][2], &face[0][0]);
    rotate_colors(&face[1][0], &face[2][1], &face[1][2], &face[0][1]);
}
void Cube::print_cube()
{
    cout  << setw(30) << setfill('=') << '\n';
    // white side
    for (int i = 0; i < 3; i++)
    {
        cout << "          ";
        for (int j = 0; j < 3; j++)
        {
            cout << "[" << this->W_side[i][j]->name << "]";
        }
        cout << "         \n";
    }
    cout << "\n";
    // orange, green, red sides
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout  << "[" << this->O_side[i][j]->name << "]";
        }
        cout << " ";
        for (int j = 0; j < 3; j++)
        {
            cout  << "[" << this->G_side[i][j]->name << "]";
        }
        cout << " ";
        for (int j = 0; j < 3; j++)
        {
            cout  << "[" << this->R_side[i][j]->name << "]";
        }
        // blue side
        cout << " ";
        for (int j = 0; j < 3; j++)
        {
            cout  << "[" << this->B_side[i][j]->name << "]";
        }
        cout << "\n";
    }
    cout << "\n";
    // yellow side
    for (int i = 0; i < 3; i++)
    {
        cout << "          ";
        for (int j = 0; j < 3; j++)
        {
            cout  << "[" << this->Y_side[i][j]->name << "]";
        }
        cout << "         \n";
    }
    cout << "\n";

    cout  << setw(30) << setfill('=') << '\n';
}
void Cube::turn_char(unsigned char user_move, int x, int y)
{
    /*
    w .... U
    s .... D
    d .... R
    a .... L
    q .... F
    e .... B
    */
    if (user_move == 'w' || user_move == 's')
    { // horizontal moves
        if (user_move == 's')
        {
            // moving D line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->G_side[2][i], &this->R_side[2][i], &this->B_side[0][i], &this->O_side[2][i]); //blue is mirrored
            }

            // moving D face
            this->rotate_face(this->Y_side);
        }
        if (user_move == 'w')
        {
            // moving U line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->O_side[0][i], &this->B_side[2][i], &this->R_side[0][i], &this->G_side[0][i]); //blue is mirrored
            }

            // moving U face
            this->rotate_face(this->W_side);
        }
    }
    else
    { // vertical moves
        if (user_move == 'd')
        {
            // moving R line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->G_side[i][2], &this->W_side[i][2], &this->B_side[i][0], &this->Y_side[i][2]);//blue is mirrored
            }
            // moving R face
            this->rotate_face(this->R_side);
        }
        if (user_move == 'a')
        {
            // moving L line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->Y_side[i][0], &this->B_side[i][2], &this->W_side[i][0], &this->G_side[i][0]);//blue is mirrored
            }
            // moving L face
            this->rotate_face(this->O_side);
        }
        if (user_move == 'q')
        {
            // moving F line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->W_side[2][i], &this->R_side[i][0], &this->Y_side[0][2-i], &this->O_side[2-i][2]);
            }
            // moving F face
            this->rotate_face(this->G_side);
        }
        if (user_move == 'e')
        {
            // moving B line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->W_side[0][i], &this->O_side[2-i][0], &this->Y_side[2][2-i], &this->R_side[i][2]);
            }
            // moving B face
            this->rotate_face_counter(this->B_side);
        }

        if (user_move == 'W' || user_move == 'S')
        { // horizontal moves
            if (user_move == 'S')
            {
                // moving D line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->O_side[2][i], &this->B_side[0][i], &this->R_side[2][i], &this->G_side[2][i]); //blue is mirrored
                }

                // moving D face
                this->rotate_face_counter(this->Y_side);
            }
            if (user_move == 'W')
            {
                // moving U line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->G_side[0][i], &this->R_side[0][i], &this->B_side[2][i], &this->O_side[0][i]); //blue is mirrored
                }

                // moving U face
                this->rotate_face_counter(this->W_side);
            }
        }
        else
        { // vertical moves
            if (user_move == 'D')
            {
                // moving R line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->Y_side[i][2], &this->B_side[i][0], &this->W_side[i][2], &this->G_side[i][2]);//blue is mirrored
                }
                // moving R face
                this->rotate_face_counter(this->R_side);
            }
            if (user_move == 'A')
            {
                // moving L line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->G_side[i][0], &this->W_side[i][0], &this->B_side[i][2], &this->Y_side[i][0]);//blue is mirrored
                }
                // moving L face
                this->rotate_face_counter(this->O_side);
            }
            if (user_move == 'Q')
            {
                // moving F line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->O_side[i][2], &this->Y_side[0][i], &this->R_side[2-i][0], &this->W_side[2][2-i]);
                }
                // moving F face
                this->rotate_face_counter(this->G_side);
            }
            if (user_move == 'E')
            {
                // moving B line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->R_side[i][2], &this->Y_side[2][2-i], &this->O_side[2-i][0], &this->W_side[0][i]);
                }
                // moving B face
                this->rotate_face(this->B_side);
            }
        }
    }
}

