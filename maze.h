#ifndef MAZE_H
#define MAZE_H

#include<stdio.h>
#include<stdlib.h>

/*_____________________MACROS______________________*/

#define MAX_WIDTH   100
#define MAX_HEIGHT  100

#define DimFileName 100  //max dimension of the file name

#define TRUE   1
#define FALSE  0

#define UP     0         //directions of moving
#define DOWN   1
#define LEFT   2
#define RIGHT  3

#define START 'S'        //name of symbols in the grid
#define END   'E'
#define WALL  '#'
#define EMPTY '.'
#define CROSS '+'        //used to mark crossed part of the maze

/*_____________________STRUCTS_____________________*/

typedef struct{                         //point of the maze
    int x;
    int y;
}Point;

typedef struct{
    char grid[MAX_WIDTH * MAX_HEIGHT]; //unidimensional array -> no void memory in between
    int height;
    int width;
}Maze;

/*____________________FUNCTIONS____________________*/

//inizialization
FILE* get_file(); 
int make_maze(Maze* maze, FILE* file);


//interract with the grid
Point move_point(Point p, int dir);                  //return the adjacent point based on the given direction
Point find_START(Maze maze);                         //return point start
char get_symbol(Maze* maze, Point p);                //return the symbol in that point of the grid
void set_symbol(Maze* maze, Point p, char symbol);   //change the symbol in that point of the grid
int is_valid(Maze* maze, Point p);                   //check if point in the grid is in the grid, is passable and has not been visited yet

//search algoritm
int path_finder(Maze* maze, Point current, int* path, int* len_path); //return TRUE if the path if found, FALSE otherwise

//print function
void print_maze(Maze* maze);
void print_path(int* path, int len_path);
void print_path_on_maze(Maze maze, int* path, int len_path, Point start);

//loop the main
int ask_redo();

#endif //MAZE_H
