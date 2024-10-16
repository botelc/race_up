#include<stdio.h>
#include "maze.h"

int main() {
    while(1){

        FILE* maze_file = get_file();

        Maze maze, original;

        while(make_maze(&maze, maze_file) == FALSE){ //if file doesn't contain a maze, ask again
            printf("Try again.\n\n");
            fclose(maze_file);
            FILE* maze_file = get_file();
        }
        //saving original maze
        original = maze;
        fclose(maze_file);

        print_maze(&maze);

        Point start = find_START(maze);
        Point current = start;

        int path[maze.height * maze.width];
        int len_path = 0;

        //quick path finder

        int max_paths = 2*((maze.width > maze.height)? maze.width : maze.height); //max number of paths necessary to find the quickest
        int (*paths[maze.height * maze.width]);

        if(path_finder(&maze, current, path, &len_path)){
            printf("Path found!\n\n");
            print_path(path, len_path);
            printf("\n");
            print_path_on_maze(original, path, len_path, start);
            printf("\n");
        }
        else printf("There is no valid path.\n\n");
        
        //ask to continue with other file
        if (ask_redo() == FALSE) return 0;
    }
}


