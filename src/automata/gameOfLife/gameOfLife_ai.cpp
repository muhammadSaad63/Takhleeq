#include <vector>
#include <iostream>
#include <raylib.h>
#include <raygui.h>
using std::cout, std::vector;
#define SIZE 450

class Node {
private:
    bool alive;
public:
    Node() : alive(false) {}
    void setStatus(const bool alive) { this->alive = alive; }
    bool isAlive() { return alive; }
};

class World {
private:
    Node grid[SIZE][SIZE];
    Node tempGrid[SIZE][SIZE];
    
    // Texture and Image for GPU-accelerated drawing
    Image frameBuffer;
    Texture2D screenTexture;
    
    int steps;
    int max;

    int countAliveNeighbors(const int row, const int col) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int r = row + i;
                int c = col + j;
                if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                    if (grid[r][c].isAlive()) count++;
                }
            }
        }
        return count;
    }

public:
    World() : steps(0), max(1) {
        // Initialize the CPU-side image buffer
        frameBuffer = GenImageColor(SIZE, SIZE, BLACK);
        // Initialize the GPU-side texture
        screenTexture = LoadTextureFromImage(frameBuffer);

        for (auto i {0}; i < SIZE; ++i) {
            for (auto j {0}; j < SIZE; ++j) {
                grid[i][j].setStatus((bool)GetRandomValue(0, 1));
            }
        }
    }

    // Destructor to clean up GPU memory
    ~World() {
        UnloadImage(frameBuffer);
        UnloadTexture(screenTexture);
    }

    void update() {
        int times = max;
        while (times--) {
            for (auto i {0}; i < SIZE; ++i) {
                for (auto j {0}; j < SIZE; ++j) {
                    auto neighBours = countAliveNeighbors(i, j);
                    if (grid[i][j].isAlive()) {
                        tempGrid[i][j].setStatus(neighBours == 2 || neighBours == 3);
                    } else {
                        tempGrid[i][j].setStatus(neighBours == 3);
                    }
                }
            }
            for (auto i {0}; i < SIZE; ++i) {
                for (auto j {0}; j < SIZE; ++j) {
                    grid[i][j] = tempGrid[i][j];
                }
            }
            steps++;
        }

        if (IsKeyDown(KEY_DOWN) && max > 1) max--;
        if (IsKeyDown(KEY_UP)) max++;
    }

    void draw() {
        // Get pointer to raw pixel data in the Image
        Color* pixels = (Color*)frameBuffer.data;

        // Update pixels based on grid state
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Raylib images are row-major: pixels[y * width + x]
                pixels[j * SIZE + i] = grid[i][j].isAlive() ? GREEN : BLACK;
            }
        }

        // Upload modified Image data to the GPU Texture
        UpdateTexture(screenTexture, frameBuffer.data);

        ClearBackground(BLACK);
        
        // Draw the texture to the screen, scaling it by 2.0 to fill the window
        DrawTextureEx(screenTexture, {0, 0}, 0.0f, 2.0f, WHITE);

        DrawText(TextFormat("Generation: %d", steps), 15, 25, 25, GOLD);
        DrawText(TextFormat("Simulation Speed: %d", max), 15, 85, 25, GOLD);
    }
};

int main() {
    InitWindow(SIZE * 2, SIZE * 2, "Game of Life - GPU Boosted");
    SetTargetFPS(60);

    World world;

    while (!WindowShouldClose()) {
        world.update();
        BeginDrawing();
            world.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}