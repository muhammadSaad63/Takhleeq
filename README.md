# an-Naml (النمل) 🐜

**an-Naml** is a high-performance C++ simulation of **Langton's Ant**, built using the **raylib** framework. It features a dual-state system that allows users to manually seed the world before letting the cellular automaton take over.

---

## 📖 Overview

Langton's Ant is a simple set of rules that leads to complex emergent behavior. After a period of "simplicity" and "chaos," the ant eventually settles into a 104-step cycle that builds a diagonal "highway."

**an-Naml** (Arabic for "The Ant") utilizes a 900x900 grid and optimized update loops to reach the highway phase in seconds rather than minutes.

---

## 🚀 Features

* **Dual Modes:** * **DRAWING:** Manually toggle cells between Black and White using the mouse.
    * **SIM:** Run the simulation at 1,000 steps per frame.
* **Toroidal Grid:** The ant wraps around the edges of the screen, allowing for infinite movement without boundary crashes.
* **Real-time Stats:** Track the total step count and coordinates directly on the HUD.
* **Clean Architecture:** Object-Oriented design with a clear separation between the `Ant` logic and the `World` environment.

---

## 🎮 Controls

| Input | Action |
| :--- | :--- |
| **Spacebar** | Toggle between **DRAWING** and **SIM** modes |
| **Left Click** | Paint cells **Black** (Drawing Mode) |
| **Right Click** | Paint cells **White** (Drawing Mode) |
| **Escape** | Close the application |

---

## 🛠️ Technical Setup

### Requirements
* **C++17** Compiler (GCC/Clang recommended)
* **raylib** (System-wide installation)
* **CMake** (3.10+)

### Build Instructions
Ensure you have `raylib` installed on your system (e.g., `sudo pacman -S raylib` on Arch).

```bash
# 1. Create a build directory
mkdir build && cd build

# 2. Configure the project
cmake ..

# 3. Build the executable
cmake --build .

# 4. Run the simulation
./an_naml

```

### Project Structure

    * ** Ant Class: Manages the ant's orientation logic (N, E, S, W), position updates, and state-based turning.

    * ** World Class: Manages the 900x900 grid, handles input polling (mouse/keyboard), and controls the rendering loop.

    * ** main.cpp: Entry point that initializes the raylib window and drives the simulation.

    * ** CMakeLists.txt: Cross-platform build script configured to link raylib and its dependencies.

---

### Credits
    This project couldn't have been possible in the least without suggestions & guidance from the following seniors of mine:
    - [Ebbi](https://github.com/DefNotEbbi)
    - [Abdul Hadi](https://github.com/abdulhadiulhaq)

### License

This project is open-source and available under the MIT License.