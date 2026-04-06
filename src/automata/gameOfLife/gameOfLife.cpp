/*
    Since you're working on a collection of cellular automata in C++, Conway's Game of Life is the perfect "hello world" for the genre. It’s played on a 2D grid of cells that are either Alive or Dead.

    Every generation (frame), the state of every cell is determined by its 8 neighbors (horizontal, vertical, and diagonal) based on these four rules:
    
    The 4 Golden Rules
        Underpopulation: Any live cell with fewer than 2 live neighbors dies.
        Survival:        Any live cell with 2 or 3 live neighbors lives on to the next generation.
        Overpopulation:  Any live cell with more than 3 live neighbors dies.
        Reproduction:    Any dead cell with exactly 3 live neighbors becomes a live cell.

    Summary Table for Implementation

    If you are writing this in your gameOfLife.cpp, you can simplify the logic into a single switch or if block after counting the neighbors:
        Current State	Live Neighbors	Next State	Reason
        Alive	            0 or 1	      Dead	    Solitude
        Alive	            2 or 3	      Alive	    Stability
        Alive	            4+	          Dead	    Overcrowding
        Dead	            3	          Alive    	Birth
*/

#include <vector>
#include <iostream>
#include <raylib.h>
#include <raygui.h>
using std::cout, std::vector;
#define SIZE 450


enum STATE {
    DRAWING,
    SIM
};

class Node{
    private:
        bool alive;

    public:
        Node() : alive(false) {}
    
        void setStatus(const bool alive){
            if (this->alive != alive){
                this->alive = alive;
            }
        }
        bool isAlive(){
            return alive;
        }
};
class World{
    private:
        Node grid[SIZE][SIZE];
        Node tempGrid[SIZE][SIZE];
        int steps;
        // STATE state;
        int max;
        // int limit;

        int countAliveNeighbors(const int row, const int col){
            // top left cell
            if (row == 0 && col == 0){
                return (
                                            grid[row][col+1].isAlive()   +
                        grid[row+1][col].isAlive()    +   grid[row+1][col+1].isAlive()
                );
            }

            // top right cell
            if (row == 0 && col == (SIZE - 1)){
                return (
                                            grid[row][col-1].isAlive()   +
                        grid[row+1][col-1].isAlive()    +   grid[row+1][col].isAlive()
                );
            }
            // down left cell
            if (row == (SIZE - 1) && col == 0){
                return (
                                            grid[row-1][col].isAlive()   +
                                            grid[row-1][col+1].isAlive()    +   grid[row][col+1].isAlive()
                );
            }
            // down right cell
            if (row == (SIZE - 1) && col == (SIZE - 1)){
                return (
                                            grid[row][col-1].isAlive()   +
                        grid[row-1][col-1].isAlive()    +   grid[row-1][col].isAlive()
                );
            }
            // left edge
            if (col == 0){
                return (
                                            grid[row-1][col].isAlive()   + grid[row-1][col+1].isAlive()   +
                        grid[row][col+1].isAlive()     +
                        grid[row+1][col].isAlive()    +   grid[row+1][col+1].isAlive()
                );
            }
            // top edge
            if (row == 0){
                return (
                                            grid[row][col-1].isAlive()   + grid[row][col+1].isAlive()   +
                        grid[row+1][col-1].isAlive()     + grid[row+1][col].isAlive()    +   grid[row+1][col+1].isAlive()
                );
            }
            // right edge
            if (col == (SIZE - 1)){
                return (
                                            grid[row-1][col-1].isAlive()   + grid[row-1][col].isAlive()   +
                        grid[row][col-1].isAlive()     + 
                        grid[row+1][col-1].isAlive()    +   grid[row+1][col].isAlive()
                );
            }
            // down edge
            if (row == (SIZE - 1)){
                return (
                                            grid[row][col-1].isAlive()   + grid[row][col+1].isAlive()   +
                        grid[row-1][col-1].isAlive()     + grid[row-1][col].isAlive()    +   grid[row-1][col+1].isAlive()
                );
            }

            // normal
            return (
                grid[row-1][col-1].isAlive() + grid[row-1][col].isAlive()   + grid[row-1][col+1].isAlive() +
                grid[row]  [col-1].isAlive() +                      grid[row]  [col+1].isAlive() +
                grid[row+1][col-1].isAlive() + grid[row+1][col].isAlive()   + grid[row+1][col+1].isAlive()
            );
        }

    public:
        World() : steps(0), max(100){
            for (auto i {0}; i < SIZE; ++i){
                for (auto j {0}; j < SIZE; ++j){
                    grid[i][j].setStatus((bool) GetRandomValue(0, 1));          // 1/3rd alive, 2/3rd dead
                }
            }
        } 

        void update(){
            int times = max;
            // if (IsKeyPressed(KEY_SPACE)) {
            //     state = (state == SIM) ? DRAWING : SIM;
            // }
            // if (state == SIM) {
                while (times--){

                    for (auto i {0}; i < SIZE; ++i){
                        for (auto j {0}; j < SIZE; ++j){
                            auto neighBours = countAliveNeighbors(i, j);

                            if (grid[i][j].isAlive()){            // alive
                                if (neighBours <= 1){
                                    tempGrid[i][j].setStatus(false);
                                }
                                else if (neighBours <= 3){
                                    tempGrid[i][j].setStatus(true);
                                }
                                else{
                                    tempGrid[i][j].setStatus(false);
                                }
                            }
                            else{           // dead cell
                                if (neighBours == 3){
                                    tempGrid[i][j].setStatus(true);
                                }
                            }
                        }
                    }

                    for (auto i {0}; i < SIZE; ++i){
                        for (auto j {0}; j < SIZE; ++j){
                            grid[i][j] = tempGrid[i][j];
                        }
                    }
                }
                // if (IsKeyDown(KEY_LEFT) && ((limit - 25) >= 0)){ limit -= 25; }
                // if (IsKeyDown(KEY_RIGHT) && (limit + 25) <= 330)                      { limit += 25; }

                if (IsKeyDown(KEY_DOWN) && ((max - 25) >= 0)){ max -= 25; }
                if (IsKeyDown(KEY_UP))                       { max += 25; }

                steps += max;
        }
        void draw(){
            ClearBackground(BLACK);

            DrawText(TextFormat("Generation: %d", steps), 15, 25, 25, GOLD);
            // DrawText(TextFormat("X: %d, Y: %d", ant.getPosX(), ant.getPosY()), 15, 55, 25, GOLD);
            DrawText(TextFormat("Simulation Speed: %d", max), 15, 85, 25, GOLD);
            // DrawText(TextFormat("Draw Size: %d", limit), 15, 115, 25, GOLD);

            for (auto i {0}; i < SIZE; ++i){
                for (auto j {0}; j < SIZE; ++j){
                    if (grid[i][j].isAlive()){
                        DrawRectangle(i * 2, j * 2, 2, 2, GREEN);      // 2 pixels drawn for every node in grid;
                    }
                }
            }
        }
};


int main(){
    InitWindow(SIZE * 2, SIZE * 2, "Game of Life");
    SetTargetFPS(60);

    World world;

    while (!WindowShouldClose())
    {
        world.update();

        BeginDrawing();

            world.draw();

        EndDrawing();
    }

    CloseWindow();
}