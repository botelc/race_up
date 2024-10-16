#include "maze.h"

FILE* get_file(){
    FILE *file;
    char file_name[DimFileName];

    printf("Enter the maze file name: ");
    scanf("%s", file_name);
    file = fopen(file_name, "r");

    while(file == NULL){
        printf("File '%s' not found.\nTry again: (e.g. maze.txt) ", file_name); 
        scanf("%s", file_name);
        file = fopen(file_name, "r");
    }
    printf("File found. Making the maze.\n");
    return file;
}

int make_maze(Maze* maze, FILE* file) {
    maze->width = 0; maze->height = 0;
    char* current = maze->grid;
    char tmp;

    while ((tmp = fgetc(file)) == '\n' || tmp == ' ');

    // First row
    if (tmp == EOF) return FALSE; // Check for EOF before processing the first row
    while (tmp != '\n') {
        while (tmp == ' ') tmp = fgetc(file);

        if (tmp == EOF) return FALSE; // Check for EOF
        if (tmp != '.' && tmp != '#' && tmp != 'S' && tmp != 'E') {
            printf("File doesn't contain a properly formatted maze.\n");
            return FALSE;
        }

        *current = tmp;
        current++;
        maze->width++;

        tmp = fgetc(file);
    }

    if (maze->width == 0) {
        printf("File doesn't contain a maze.");
        return FALSE;
    }

    maze->height++;

    while (1) {
        for (int j = 0; j < maze->width; j++, current++) {
            while ((tmp = fgetc(file)) == ' ');

            if (tmp == EOF) return TRUE; // Check for EOF
            if (j == 0 && tmp == '\n'){ //when the file continues with space and newline
                printf("Part of file was ignored.\n\n");
                return TRUE;

            }

            if (tmp != '.' && tmp != '#' && tmp != 'S' && tmp != 'E') {
                printf("File doesn't contain a properly formatted maze.\n");
                return FALSE;
            }
            *current = tmp;
        }
        maze->height++;
        while ((tmp = fgetc(file)) == ' ');
        if (tmp == EOF) return TRUE; // Check for EOF
        if (tmp != '\n') {
            printf("File doesn't contain a properly formatted maze.\n");
            return FALSE;
        }
    }
}

void print_maze(const Maze* maze) {
    // Iterate over each row of the maze
    for (int i = 0; i < maze->height; i++) {
        // Iterate over each column of the maze
        for (int j = 0; j < maze->width; j++) {
            // Print the corresponding symbol using the one-dimensional index
            printf("%c ", maze->grid[i * maze->width + j]);
        }
        printf("\n"); // Move to the next line after each row
    }
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
        default:
            return (Point){-1, -1};
    }
}


Point find_S(Maze maze) {
    for (int i = 0; i < maze.height * maze.width; i++) {
        if (maze.grid[i] == 'S') {
            return (Point){i / maze.width, i % maze.width};
        }
    }
    return (Point){-1, -1};
}

char get_symbol(Maze* maze, Point p){
    return maze->grid[maze->width * p.x + p.y];
}

int is_valid(Maze* maze, Point p){
    // check borders
    if (p.x < 0 || p.x >= maze->height || p.y < 0 || p.y >= maze->width) {
        return FALSE;
    }
    char sym = get_symbol(maze,p);
    if (sym == '#' || sym == 'V') {
        return FALSE;
    }
    
    return TRUE;
}

int path_finder(Maze* maze, Point current, int* path, int* len_path){

    if (!is_valid(maze, current)) return FALSE;
    if (get_symbol(maze, current) == 'E') return TRUE;

    //mark this point like already crossed
    maze->grid[maze->width * current.x + current.y] = 'V'; //I know it's ugly

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

void print_path(int* path, int len_path) {
    for (int i = 0; i < len_path; i++) {
        switch (path[i]) {
            case UP:
                printf("UP ");
                break;
            case DOWN:
                printf("DOWN ");
                break;
            case LEFT:
                printf("LEFT ");
                break;
            case RIGHT:
                printf("RIGHT ");
                break;
            default:
                printf("UNKNOWN ");
                break;
        }
    }
    printf("\n");
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
