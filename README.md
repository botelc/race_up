# Maze Project - Race_UP assignament

## Description

This project is a C application that allows users to manage a maze defined in a text file. Users can load a maze, visualize it, and the programm will find a path from the starting point 'S' to the endpoint 'E'. The project utilizes a search algorithm to navigate through the maze.

## Table of Contents

- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)


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
   gcc main.c main.h -o maze
```
5. Run the program with:

```bash
  ./maze
```
6. Follow the instructions.

### DISCLAIMER - Outdated compiler

In the unlikely event that an outdated compiler is used, functionality is not guaranteed, as the syntax `(Point){x, y}` may not be supported. It is recommended to use a more recent compiler for  compatibility.

## Usage


