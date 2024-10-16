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
Point move_point(Point p, int dir);
Point find_START(Maze maze);
char get_symbol(Maze* maze, Point p);
void set_symbol(Maze* maze, Point p, char symbol);
int is_valid(Maze* maze, Point p);

//search algoritm
int path_finder(Maze* maze, Point current, int* path, int* len_path);

//print function
void print_maze(Maze* maze);
void print_path(int* path, int len_path);
void print_path_on_maze(Maze maze, int* path, int len_path, Point start);

//loop the main
int ask_redo();

#endif //MAZE_H