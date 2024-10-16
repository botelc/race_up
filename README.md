# Maze Project - Race_UP assignament

## Description

This project is a C application that allows users to manage a maze defined in a text file. Users can load a maze, visualize it, and the programm will find a path from the starting point `S` to the endpoint `E`. The project utilizes a search algorithm to navigate through the maze.

## Table of Contents

- [Project Structure](#project-structure)
- [Installation](#installation)
- [Workflow](#workflow)
- [Explanation](#explanation)


## Project Structure

The project consists of 3 files:
- `main.c`: contains the code of main.
- `maze.h`: the header with all the MACROS, struct and functions.
- `maze.c`: contains the actual code of the functions.

## Installation

1. Download the ZIP file of the project.
1. Unzip in a folder.
2. Prepare one or more text files containing the mazes and put them in the same folder.
3. Open the terminal in the folder.
4. Compile the project using:

```bash
   gcc main.c maze.c -o maze
```
5. Run the program with:

```bash
  ./maze
```

### DISCLAIMER - Outdated compiler

In the unlikely event that an outdated compiler is used, functionality is not guaranteed, as the syntax `(Point){x, y}` may not be supported. It is recommended to use a more recent compiler for  compatibility.


## Workflow

1. **File Input**: 
   - Upon starting the program, the user is prompted to enter the name of a text file containing the maze layout.

2. **Maze Format**: 
   - The text file must contain the starting point `S` and the endpoint `E`, along with walls represented by `#` and open paths by `.`. Whitespace and newlines at the beginning or whitespace between characters will be ignored.

3. **Validation**: 
   - The program will reject any files that contain invalid characters (anything other than `S`, `E`, `.`, `#`, whitespace, and newlines) before the end of the grid. Additionally, any content following a blank line after the maze will be ignored.

4. **Processing the Maze**:
   - Once a valid maze is recognized, the program will:
     - Print the maze layout.
     - Search for a path from `S` to `E`.
     - If a path is found, it will display the series of movements (e.g., `['UP', 'DOWN', ...]`).
     - Finally, it will print the maze again, this time marking the path.

5. **Multiple File Handling**: 
   - The program allows for processing multiple maze files during a single run. After completing the process for one file, the user will be prompted to enter another file name or exit the program.
  

## Explanation


The first part of the program handles the file request. It attempts to process the file, saving the grid into a Maze struct as the first part of a character array, while also calculating its dimensions. If it fails to initialize the maze correctly, it will prompt for another file.

A one-dimensional array is chosen to avoid unnecessary spaces between the rows. The program will then search for the starting point and implement a depth-first search (DFS) algorithm due to its straightforward implementation. This approach simulates real-life pathfinding behavior, as it moves forward until it encounters a dead end or a previously visited point, then backtracks to find an unexplored area and continues.

When the endpoint is found, the algorithm terminates. If there are no more places to go, the algorithm returns with a failure.

The code should be quite readable, with brief comments available in all three files.
