#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "cube.hpp"
#include <GL/glut.h>
#include <random>

using namespace std;

// colors for rendering
#define WHITE 1.0f, 1.0f, 1.0f 
#define YELLOW 1.0f, 1.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define ORANGE 0.7f, 0.3f, 0.0f

Sticker::Sticker(int n, GLfloat r, GLfloat g, GLfloat b)
{

    this->name = n;
    this->color = Color{r, g, b};
}

Cube::Cube()
{
    Sticker white(1, WHITE);
    Sticker yellow(2, YELLOW);
    Sticker green(3, GREEN);
    Sticker blue(4, BLUE);
    Sticker red(5, RED);
    Sticker orng(6, ORANGE);
    reset();
}
void Cube::rotate_colors(Sticker **one, Sticker **two, Sticker **three, Sticker **four)
{ // one->two, two->three, three->four, four->one
    Sticker *temp = *one;
    *one = *four;
    *four = *three;
    *three = *two;
    *two = temp;
}
void Cube::rotate_face(Sticker *face[3][3])
{
    rotate_colors(&face[0][0], &face[0][2], &face[2][2], &face[2][0]);
    rotate_colors(&face[0][1], &face[1][2], &face[2][1], &face[1][0]);
}
void Cube::rotate_face_counter(Sticker *face[3][3])
{
    rotate_colors(&face[2][0], &face[2][2], &face[0][2], &face[0][0]);
    rotate_colors(&face[1][0], &face[2][1], &face[1][2], &face[0][1]);
}

void Cube::turn_char(unsigned char user_move)
{
    /*
    w .... U
    s .... D
    d .... R
    a .... L
    q .... F
    e .... B
    uppercase....counterclockwise
    */
    if (user_move == 'w' || user_move == 's')
    { // horizontal moves

        if (user_move == 's')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving D line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->G_side[2][i], &this->R_side[2][i], &this->B_side[0][i], &this->O_side[2][i]); // blue is mirrored
            }

            // moving D face
            this->rotate_face(this->Y_side);
        }
        if (user_move == 'w')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving U line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->O_side[0][i], &this->B_side[2][i], &this->R_side[0][i], &this->G_side[0][i]); // blue is mirrored
            }

            // moving U face
            this->rotate_face(this->W_side);
        }
    }
    else
    { // vertical moves
        if (user_move == 'd')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving R line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->G_side[i][2], &this->W_side[i][2], &this->B_side[i][0], &this->Y_side[i][2]); // blue is mirrored
            }
            // moving R face
            this->rotate_face(this->R_side);
        }
        if (user_move == 'a')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving L line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->Y_side[i][0], &this->B_side[i][2], &this->W_side[i][0], &this->G_side[i][0]); // blue is mirrored
            }
            // moving L face
            this->rotate_face(this->O_side);
        }
        if (user_move == 'q')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving F line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->W_side[2][i], &this->R_side[i][0], &this->Y_side[0][2 - i], &this->O_side[2 - i][2]);
            }
            // moving F face
            this->rotate_face(this->G_side);
        }
        if (user_move == 'e')
        {
            if (this->scramble_state)
            {
                this->start_time = std::chrono::steady_clock::now();
                this->scramble_state = false;
                this->solving = true;
            }
            // moving B line
            for (int i = 0; i < 3; i++)
            {
                this->rotate_colors(&this->W_side[0][i], &this->O_side[2 - i][0], &this->Y_side[2][2 - i], &this->R_side[i][2]);
            }
            // moving B face
            this->rotate_face_counter(this->B_side);
        }

        if (user_move == 'W' || user_move == 'S')
        { // horizontal moves
            if (user_move == 'S')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                    this->solving = true;
                }
                // moving D line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->O_side[2][i], &this->B_side[0][i], &this->R_side[2][i], &this->G_side[2][i]); // blue is mirrored
                }

                // moving D face
                this->rotate_face_counter(this->Y_side);
            }
            if (user_move == 'W')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                    this->solving = true;
                }
                // moving U line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->G_side[0][i], &this->R_side[0][i], &this->B_side[2][i], &this->O_side[0][i]); // blue is mirrored
                }

                // moving U face
                this->rotate_face_counter(this->W_side);
            }
        }
        else
        { // vertical moves
            if (user_move == 'D')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                    this->solving = true;
                }
                // moving R line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->Y_side[i][2], &this->B_side[i][0], &this->W_side[i][2], &this->G_side[i][2]); // blue is mirrored
                }
                // moving R face
                this->rotate_face_counter(this->R_side);
            }
            if (user_move == 'A')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                    this->solving = true;
                }
                // moving L line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->G_side[i][0], &this->W_side[i][0], &this->B_side[i][2], &this->Y_side[i][0]); // blue is mirrored
                }
                // moving L face
                this->rotate_face_counter(this->O_side);
            }
            if (user_move == 'Q')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                    this->solving = true;
                }
                // moving F line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->O_side[i][2], &this->Y_side[0][i], &this->R_side[2 - i][0], &this->W_side[2][2 - i]);
                }
                // moving F face
                this->rotate_face_counter(this->G_side);
            }
            if (user_move == 'E')
            {
                if (this->scramble_state)
                {
                    this->start_time = std::chrono::steady_clock::now();
                    this->scramble_state = false;
                }
                // moving B line
                for (int i = 0; i < 3; i++)
                {
                    this->rotate_colors(&this->R_side[i][2], &this->Y_side[2][2 - i], &this->O_side[2 - i][0], &this->W_side[0][i]);
                }
                // moving B face
                this->rotate_face(this->B_side);
            }
        }
    }
}

bool Cube::is_solved()
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((*W_side[i][j]).name != 1){
                return false;
            }
            if ((*Y_side[i][j]).name != 2)
            {
                return false;
            }
            if ((*G_side[i][j]).name != 3)
            {
                return false;
            }
            if ((*B_side[i][j]).name != 4)
            {
                return false;
            }
            if ((*R_side[i][j]).name != 5)
            {
                return false;
            }
            if ((*O_side[i][j]).name != 6)
            {
                return false;
            }
        }
    }
    if (solving)
    {
        end_time = std::chrono::steady_clock::now();
        solving = false;
    }
    return true;
}

void Cube::reset()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->W_side[i][j] = new Sticker(1, WHITE); // coords [y][x]{{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
            this->Y_side[i][j] = new Sticker(2, YELLOW);
            this->G_side[i][j] = new Sticker(3, GREEN);
            this->B_side[i][j] = new Sticker(4, BLUE);
            this->R_side[i][j] = new Sticker(5, RED);
            this->O_side[i][j] = new Sticker(6, ORANGE);
        }
    }
    solving = false;
    scramble_state=false;
    start_time = std::chrono::steady_clock::now();
    end_time = std::chrono::steady_clock::now();
}
