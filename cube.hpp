#include <string>
#include <GL/glut.h>

struct Color{
    GLfloat r,g,b;
    // Color(GLfloat x, GLfloat y, GLfloat z);
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


    Sticker *W_side[3][3] = {{}, {}, {}}; // coords [y][x]{{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}};
    Sticker *Y_side[3][3] = {};
    Sticker *G_side[3][3] = {};
    Sticker *B_side[3][3] = {};
    Sticker *R_side[3][3] = {};
    Sticker *O_side[3][3] = {};
    void print_cube();
    void turn_char(unsigned char user_move, int x, int y);
};

