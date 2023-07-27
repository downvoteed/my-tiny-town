# My tiny Town

## About this project

My tiny town is a simple CAD city software inspired by some games I used to play.
Behind this project lies one week of work and much ~~fun~~ progress made.

This project doesn't have any pretension, and it's only a way for me to learn new things through a toy project.

## Requirements

- CMake
- OpenGL

## Dependencies

- Glad
- GLFW
- assimp

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/MyTinyTown
```

![](https://i.imgur.com/utWgnTy.png)


## Usage

### Controls

    - MouseWheel: Zoom in/out
    - Left click: Select object
    - Left click + drag: Move object
    - Left click + move mouse: move camera
	- Right click: rotate camera



## Know issues
    - A lot of OpenGL errors
    - Freeze on loading

## TODO
    - Shadows
    - Refactor model class
