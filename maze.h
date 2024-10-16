#ifndef MAZE_H
#define MAZE_H

#include<stdio.h>
#include<stdlib.h>

#define MAX_LINES 100
#define MAX_LEN_LINE 100

#define DimFileName 100
#define TRUE 1
#define FALSE 0

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct{
    int x;
    int y;
}Point;

typedef struct{
    char grid[MAX_LINES * MAX_LEN_LINE];
    int height;
    int width;
}Maze;


FILE* get_file();
int make_maze(Maze* maze, FILE* file);
void print_maze(const Maze* maze);

Point move_point(Point p, int dir);

Point find_S(Maze maze);
char get_symbol(Maze* maze, Point p);

int is_valid(Maze* maze, Point p);
int path_finder(Maze* maze, Point current, int* path, int* len_path);
void print_path(int* path, int len_path);

int ask_redo();

#endif
