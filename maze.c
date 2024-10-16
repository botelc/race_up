#include <stdio.h>
#include "maze.h"

FILE* get_file(){
    FILE *file;
    char file_name[DimFileName];

    printf("Enter the maze file name: ");
    scanf("%s", file_name);
    file = fopen(file_name, "r");
    //check file
    while(file == NULL){
        printf("File '%s' not found.\n\nTry again: (e.g. maze.txt) ", file_name); 
        scanf("%s", file_name);
        file = fopen(file_name, "r");
    }
    //file checked and opened
    printf("File found. Making the grid.\n\n");
    return file;
}

int make_maze(Maze* maze, FILE* file) {
    maze->width = 0; maze->height = 0;
    char* current = maze->grid;
    char tmp;

    while ((tmp = fgetc(file)) == '\n' || tmp == ' ');

    // First row
    if (tmp == EOF){ // Check for EOF before processing the first row
        printf ("File doesn't contain a maze.");
        return FALSE;
        } 
    while (tmp != '\n') {
        while (tmp == ' ') tmp = fgetc(file);

        if (tmp == EOF) return FALSE; // Check for EOF
        if (tmp != EMPTY && tmp != WALL && tmp != START && tmp != END) {
            printf("File doesn't contain a properly formatted maze.\n");
            return FALSE;
        }

        *current = tmp;
        current++;
        maze->width++; //calculating lenght of the first row

        tmp = fgetc(file);
    }

    //first row initialize, now width is known
    maze->height++;
    while (1) {
        for (int j = 0; j < maze->width; j++, current++) {
            while ((tmp = fgetc(file)) == ' ');

            if (tmp == EOF) return TRUE; // Check for EOF
            if (j == 0 && tmp == '\n'){ //when the file continues with space and newline
                printf("Part of the file was ignored.\n\n");
                return TRUE;

            }

            if (tmp != EMPTY && tmp != WALL && tmp != START && tmp != END) {
                printf("File doesn't contain a properly formatted maze.\n");
                return FALSE;
            }
            *current = tmp;
        }
        maze->height++; //another row initialized
        while ((tmp = fgetc(file)) == ' ');
        if (tmp == EOF){
            printf("\n");
            return TRUE; // End of the maze
        }
        if (tmp != '\n') {
            printf("File doesn't contain a properly formatted maze.\n");
            return FALSE;
        }
    }
}

void print_maze(Maze* maze) {
    printf("+ ");
    for(int i = 0; i < maze->width; i++) printf("- ");
    printf("+\n");
    for (int i = 0; i < maze->height; i++) {
        printf("| ");
        for (int j = 0; j < maze->width; j++) {
            char c = get_symbol(maze, (Point){i,j});
            if (c == EMPTY) c = ' ';
            printf("%c ", c);
        }
        printf("|\n");
    }
    printf("+ ");
    for(int i = 0; i < maze->width; i++) printf("- ");
    printf("+\n");
}

Point move_point(Point p, int dir) {
    switch (dir) {
        case UP:
            return (Point){p.x - 1, p.y}; 
        case DOWN:
            return (Point){p.x + 1, p.y}; 
        case LEFT:
            return (Point){p.x, p.y - 1}; 
        case RIGHT:
            return (Point){p.x, p.y + 1};
    }
}


Point find_START(Maze maze) {
    for (int i = 0; i < maze.height * maze.width; i++) {
        if (maze.grid[i] == START) {
            return (Point){i / maze.width, i % maze.width};
        }
    }
    return (Point){-1, -1};
}

char get_symbol(Maze* maze, Point p){
    return maze->grid[maze->width * p.x + p.y];
}
void set_symbol(Maze* maze, Point p, char symbol){
    maze->grid[maze->width * p.x + p.y] = symbol;
}

int is_valid(Maze* maze, Point p){
    // check borders
    if (p.x < 0 || p.x >= maze->height || p.y < 0 || p.y >= maze->width) {
        return FALSE;
    }
    char sym = get_symbol(maze,p);
    if (sym == WALL || sym == CROSS) {
        return FALSE;
    }
    
    return TRUE;
}

int path_finder(Maze* maze, Point current, int* path, int* len_path){

    if (!is_valid(maze, current)) return FALSE;
    if (get_symbol(maze, current) == END) return TRUE;

    //mark this point like already crossed
    set_symbol(maze, current, CROSS);

    //do the four movements
    for (int direction = UP; direction <= RIGHT; direction++) {
        //add step to path
        path[*len_path] = direction;
        (*len_path)++;

        if (path_finder(maze, move_point(current, direction), path, len_path)) {
            return TRUE; // path found
        }

        //remove last move
        (*len_path)--;
    }

    //if we arrive here, there is no path from current point

return FALSE;
}

int quick_path_finder();

void print_path(int* path, int len_path) {
    printf("[");
    for (int i = 0; i < len_path - 1; i++) {
        printf("\'");
        switch (path[i]) {
            case UP:
                printf("UP");
                break;
            case DOWN:
                printf("DOWN");
                break;
            case LEFT:
                printf("LEFT");
                break;
            case RIGHT:
                printf("RIGHT");
                break;
        }
        printf("\',");
    }
    printf("\'");
    switch (path[len_path -1]) {
        case UP:
            printf("UP");
            break;
        case DOWN:
            printf("DOWN");
            break;
        case LEFT:
            printf("LEFT");
            break;
        case RIGHT:
            printf("RIGHT");
            break;
    }
    printf("\',");    
    printf("]\n");
}

void print_path_on_maze(Maze maze, int* path, int len_path, Point start){

    Point current = start;
    for(int i = 0; i < len_path-1; i++){
        current = move_point(current, path[i]);
        set_symbol(&maze, current, CROSS);
    }

    print_maze(&maze);

}

int ask_redo(){
    printf("Do you want to import another maze?: [y/n] ");
    char choice[10];
    scanf("%s",&choice);
    switch(choice[0]){

        case('y'): return TRUE;
        case('Y'): return TRUE;

        case('N'): return FALSE;
        case('n'): return FALSE;

        default:{
            printf("Invalid choice.\n");
            return ask_redo();
        }
    }
}
