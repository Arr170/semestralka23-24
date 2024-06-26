#include <string>
#include <GL/glut.h>
#include <time.h>
#include <chrono>

struct Color{
    GLfloat r,g,b;
};



struct Sticker
{
    int name;
    Color color;
    

    Sticker(int n, float r, float g, float b);
};

class Cube
{
    

    /* original state:
            W W W
            W W W
            W W W

     O O O  G G G  R R R
     O O O  G G G  R R R
     O O O  G G G  R R R

            Y Y Y
            Y Y Y
            Y Y Y

            B B B
            B B B
            B B B

    */
public:
    Cube ();
    void rotate_colors(Sticker **one, Sticker **two, Sticker **three, Sticker **four);
    void rotate_face(Sticker *face[3][3]);

    void rotate_face_counter(Sticker *face[3][3]);

    bool scramble_state = false;
    bool solving = false;
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
    Sticker *W_side[3][3] = {{}, {}, {}}; // coords [y][x]{{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
    Sticker *Y_side[3][3] = {};
    Sticker *G_side[3][3] = {};
    Sticker *B_side[3][3] = {};
    Sticker *R_side[3][3] = {};
    Sticker *O_side[3][3] = {};
    void print_cube();
    void turn_char(unsigned char user_move);
    bool is_solved();
    void reset();
};

