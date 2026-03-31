/*
    Langton's Ant is a cellular automaton that operates on a grid of black and white cells using a very simple set of rules. Despite these simple conditions, it leads to surprisingly complex emergent behavior.

    The "world" consists of a 2D grid of cells that can be in one of two states: ON (Black) or OFF (White). The Ant itself has a location and a direction (North, South, East, or West).
    The Fundamental Rules

    At every time step, the Ant follows these four conditions based on the color of the square it is currently standing on:
        
        At a White Square:
            Turn 90° right.
            Flip the color of the square to Black.
            Move forward one unit.

        At a Black Square:
            Turn 90° left.
            Flip the color of the square to White.
            Move forward one unit.

    The Three Stages of Behavior
        When you run the simulation, the Ant almost always follows a specific "evolutionary" path:
            Simplicity (First 0–500 steps):
                The Ant creates very simple, often symmetrical patterns. It stays within a small area, flipping squares back and forth.
            Chaos (500–10,000 steps):
                The pattern becomes a pseudo-random "cloud" of black and white pixels. There is no discernible order, and it looks like a random walk across the grid.
            The Highway (After ~10,000 steps):
                The Ant eventually hits a recurring cycle of 104 steps. This cycle causes it to build a diagonal "highway"—a repeating pattern that moves infinitely in one direction.f

    Mathematical Properties
        Universality: Langton's Ant is Turing Complete. This means that, theoretically, you could build a computer capable of any calculation just using a massive grid and a specific starting arrangement of black and white squares.
        Reversibility: The rules are reversible. If you know the state of the grid and the Ant’s position/direction, you can calculate exactly where it was in the previous step.
        Grown's Identity: It has been proven that the Ant's trajectory is always unbounded—it will never get stuck in a finite box; it will always keep moving further away from its starting point eventually.

    Multiple Colors (Extensions)
        You can extend the conditions to more than two colors (e.g., Red, Green, Blue). In this case, you assign a turn (Left or Right) to each color. For example:
            RLR: (Red: Right, Blue: Left, Green: Right).
            These variations produce incredibly varied patterns, including spirals and massive symmetrical "cardioid" shapes.
*/

#include <vector>
#include <iostream>
#include <raylib.h>
#include <raygui.h>
using std::cout, std::vector;
#define SIZE 900


enum STATE {
    DRAWING,
    SIM
};

class Ant{
    private:
        char    orientations[4] { 'N', 'E', 'S', 'W' };
        char    orientation     { 'N' };
        // Vector2 position        { Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2} };
        Vector2 position        { Vector2{(float)SIZE/2, (float)SIZE/2} };
        

        void turnLeft(){
            for (auto c {0}; c < 4; ++c){
                if (orientations[c] == orientation){
                    if   (c == 0){ c = 3; }
                    else         { c--; }
                    
                    orientation = orientations[c];
                    return;
                }
            }
        }
        void turnRight(){
            for (auto c {0}; c < 4; ++c){
                if (orientations[c] == orientation){
                    if   (c == 3){ c = 0; }
                    else         { c++; }
                    
                    orientation = orientations[c];
                    return;
                }
            }
        }
        void moveNorth(){ position.y--; }
        void moveEast() { position.x++; }
        void moveSouth(){ position.y++; }
        void moveWest() { position.x--; }

    public:
    
        int getPosY(){ return position.y; }             // returns the ants X-position
        int getPosX(){ return position.x; }             // returns the ants Y-position

        // turns (changes orientation based upon cell color)
        void turn(const char& cellColor){
            ((cellColor == 'W')? turnRight() : turnLeft());
        }
        
        // move (update position based upon current orientation)
        void move(){
            switch (orientation){
                case 'N': { moveNorth(); break; }
                case 'E': { moveEast();  break; }
                case 'S': { moveSouth(); break; }
                case 'W': { moveWest();  break; }
            }


            if (position.x > 850) {
                position.x = 0;
            }
            if (position.x <= 1){
                position.x = SIZE -1 ;
            }
            if (position.y > 850) {
                position.y = 0;
            }
            if (position.y <= 1) {
                position.y = SIZE - 1;
            }
        }
};
class World{
    private:
        // vector<vector<char>> grid;
        char grid[SIZE][SIZE];
        Ant ant;
        int steps;
        STATE state;
        int max;
        int limit;

    public:
        World() : steps(0), state(DRAWING), max(100), limit(10) {
            // grid.reserve(GetScreenWidth());
            for (auto i {0}; i < GetScreenWidth(); ++i){
                for (auto j {0}; j < GetScreenHeight(); ++j){
                    grid[i][j] = 'W';
                }
            }
        } 

        void update(){
            int times = max;
            if (IsKeyPressed(KEY_SPACE)) {
                state = (state == SIM) ? DRAWING : SIM;
            }
            if (state == SIM) {
                while (times--){
                    char&  cellColor = grid[ant.getPosX()][ant.getPosY()];

                    ant.turn(cellColor);
                    ant.move();

                    cellColor = (cellColor == 'W') ? 'B' : 'W';

                    steps++;
                }
            } else {
                Vector2 pos = GetMousePosition();
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    grid[(int)pos.x][(int)pos.y] = 'B';
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.x + i) > SIZE) { break; }
                        grid[(int)pos.x+i][(int)pos.y] = 'B';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.x - i) < 0) { break; }
                        grid[(int)pos.x - i][(int)pos.y] = 'B';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.y + i) > SIZE) { break; }
                        grid[(int)pos.x][(int)pos.y + i] = 'B';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.y - i) < 0) { break; }
                        grid[(int)pos.x][(int)pos.y - i] = 'B';
                    }
                }
                if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                    grid[(int)pos.x][(int)pos.y] = 'W';
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.x + i) > SIZE) { break; }
                        grid[(int)pos.x+i][(int)pos.y] = 'W';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.x - i) < 0) { break; }
                        grid[(int)pos.x - i][(int)pos.y] = 'W';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.y + i) > SIZE) { break; }
                        grid[(int)pos.x][(int)pos.y + i] = 'W';
                    }
                    for (auto i {0}; i < limit; ++i){
                        if ((pos.y - i) < 0) { break; }
                        grid[(int)pos.x][(int)pos.y - i] = 'W';
                    }

                }
                if (IsKeyDown(KEY_LEFT) && ((limit - 25) >= 0)){ limit -= 25; }
                if (IsKeyDown(KEY_RIGHT) && (limit + 25) <= 330)                      { limit += 25; }

                if (IsKeyDown(KEY_DOWN) && ((max - 25) >= 0)){ max -= 25; }
                if (IsKeyDown(KEY_UP))                       { max += 25; }
            }
        }
        void draw(){
            ClearBackground(WHITE);

            DrawText(TextFormat("Steps: %d", steps), 15, 25, 25, GOLD);
            DrawText(TextFormat("X: %d, Y: %d", ant.getPosX(), ant.getPosY()), 15, 55, 25, GOLD);
            DrawText(TextFormat("Simulation Speed: %d", max), 15, 85, 25, GOLD);
            DrawText(TextFormat("Draw Size: %d", limit), 15, 115, 25, GOLD);

            for (auto i {0}; i < GetScreenWidth(); ++i){
                for (auto j {0}; j < GetScreenHeight(); ++j){
                    if (grid[i][j] == 'B') DrawPixel(i, j, BLACK);
                }
            }
        }
};


int main(){
    InitWindow(SIZE,SIZE, "Langton's Ant");
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