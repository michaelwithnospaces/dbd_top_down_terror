# Dead by Daylight: Top-Down Terror

A top-down survival game inspired by **Dead by Daylight**, built using **raylib**.

## Features
- Player movement with `WASD` keys.
- Generator interaction system (similar to **Dead by Daylight** mechanics).
- Skill check system for generator progress.
  
## Prerequisites

### Required Tools:
- **raylib** library for rendering.
- **g++** or any other C++ compiler that supports C++11 or later.
- **bash** for running the build script (in case you're on Windows, you can use **WSL**).

### Setting Up raylib:
To compile and run the project, you'll need to have **raylib** installed. You can follow these steps to install raylib:

1. **On Ubuntu (WSL or native):**
   ```bash
   sudo apt update
   sudo apt install build-essential libgl1-mesa-dev libopenal-dev libx11-dev
   sudo apt install raylib-dev

### Instructions for Your `build.bash`

Make sure your `build.bash` script properly compiles the project. Here's an example `build.bash`:

```bash
#!/bin/bash

# Compile the project
g++ main.cpp Generator.cpp Terrain.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Run the game
./game