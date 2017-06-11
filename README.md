# Wolf3d

### What is Wolf3d?
Wolf3d is a simple raycasting program to generate 2.5-d maps. 
It uses a very lightweight graphics library, minilibx, built on top of OpenGL.

### System Requirements
1. Mac OS X El Capitan Version 10.11.6
2. OpenGL 3.*

### Usage
Wolf3d program takes the path to a file describing the map.
The map file should consist of a n * m integer matrix where (integers 0 ~ 8 represent different textures)

Once launched, the following inputs are supported during the program.
1. Turn left and right using left and right arrow keys.
2. Move back and forth using up and down arrow keys.

### Images
![Map](http://i.imgur.com/diT0RRz.png)

### To do list
1. Multithread the drawing of the image. (possibly in OpenCL)
2. Add a weapon and its functionalities
3. Add sprites.
