#include "maze.h"

int main() {
    while(1){

        FILE* maze_file = get_file();

        Maze maze;
        make_maze(&maze, maze_file);
        fclose(maze_file);

        print_maze(&maze);

        Point start = find_S(maze);
        Point actual = start;

        int path[maze.height * maze.width];
        int len_path = 0;

        if(path_finder(&maze, actual, path, &len_path)){
            printf("Path found!\n");
            print_path(path, len_path);
        }
        else printf("There is no valid pass.\n\n");

        if (ask_redo() == FALSE) return 0;
    }
}


