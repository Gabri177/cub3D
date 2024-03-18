# So Long - 42 School Project
![so_long](https://github.com/Gabri177/so_long/assets/152025617/507ddca0-33f5-42e7-a118-0f4834dbaeb9)

## Introduction
&emsp;&emsp;**"So Long"** is a small 2D game project designed as part of the curriculum at 42 School. The main objective of this project is to introduce students to graphical programming and reinforce their skills in C programming, particularly in managing graphics, creating simple game logic, and handling user inputs. The game is built upon the principles of a classic tile-based game where the player must navigate through a map to reach an exit, collect items, and possibly avoid or interact with obstacles or enemies.

## Technical Stack
**Programming Language**:    

&emsp;&emsp;C, with strict adherence to the Norminette coding standard. 

**Graphics Library**:    

&emsp;&emsp;MiniLibX, a lightweight graphical library provided by 42 School, facilitating basic graphics operations like window management, image manipulation, and event handling.  

**Environment**:    

&emsp;&emsp;Developed and tested in Unix-based systems (macOS or Linux).  

**Utilities**:    

* Make: For compiling the project and managing builds.
* Git: For version control.

## Tools and Utilities:  


- **Map File Reading**: Maps are read from files ending with '.ber', ensuring the game loads different levels or layouts.

- Map Validation

  **Validates the map for legality**:

    - Must contain at least one exit ('E'), one collectible ('C'), an empty space ('0'), and a starting position ('P').
    - Surrounded by walls ('1') and contains no invalid characters.
    - The layout must form a rectangle.

- **Depth-First Search Algorithm**: Used to verify the solvability of the map, ensuring that there is a path from the start to the exit.

- **Custom Data Types**: Redefined a new variable type in the header file, essentially a three-dimensional pointer matrix, and structured variables used as elements within this matrix.

- **Element Detection**: Implemented custom functions for detecting and interacting with elements within the matrix.

- **Graphics with MiniLibX**: Utilized MiniLibX for window creation, keyboard input handling, and graphical updates (e.g., moving the player, redrawing backgrounds and walls).

- **Event Hooking**: Managed window closure, character movements, and other key events through MiniLibX's hook system.

- Error Handling

    **Robust error management to handle various issues, including**:

    - Graphics loading failures.
    - Map reading errors.
    - Invalid map configurations.
    - Illegal map characters.
    - Matrix setup issues.
    - Memory errors.
    - And more.

## Project Structure
&emsp;&emsp;Source Files: Contains all the C source code files (.c) necessary for the game logic, rendering, event handling, and other utilities.
Header Files: Includes all the header files (.h) defining structures, constants, and function prototypes used throughout the project.
Maps: A directory for game assets such as textures, sprites, maps, and sound effects (if applicable).
Makefile: Contains rules for compiling the project, cleaning up object files, and fully recompiling the project.
## Features
**Map Parsing**: 

&emsp;&emsp;Load and parse game maps from a file, with the ability to customize maps for varied gameplay experiences.
Graphics Rendering:      
&emsp;&emsp;Utilize MiniLibX to render the game scene, including tiles, player character, collectibles, and exit.

**Player Movement**:      

&emsp;&emsp;Handle keyboard inputs to move the player character through the map, collecting items and navigating to the exit.
Collision Detection: Implement logic to detect collisions with walls, collectibles, and other game elements.

**Game Status**:    

&emsp;&emsp;Keep track of collectibles picked up and display game status, such as the number of moves or items collected.

**Exit Mechanism**:    

&emsp;&emsp;Allow the player to exit the game upon reaching the goal, after collecting all necessary items.

## Getting Started

* Clone the Repository: Clone this project to your local machine using Git.
```bash
git clone https://github.com/Gabri177/so_long.git
```
* Compile the Project: Navigate to the project directory and run the make command to compile the project.
```bash
cd so_long
make
```
* Run the Game: After compilation, start the game by running the executable with a map file.
```bash
./so_long maps/map.ber
```
## Contribution
Contributions to "So Long" are welcome. Whether it's bug fixes, feature additions, or improvements to the code, feel free to fork the repository and submit a pull request.
