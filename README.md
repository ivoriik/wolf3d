# wolf3d

UNIT Factory/42 School project.

## Description

3rd project of the Graphic Branch of 42. Wolf3d is a project aimed at reproducing the principle of ray casting in the famous game Wolfeinstein. For this we have to realize in pure C all necessary functions with the minimal use of graphic libraries. Allowed functions: open a window, lit the pixes and handle events (other functions could be allowed to complete the bonus part).
This game has not a real goal, you can simply explore the mazes.

More about project: [Subject](https://github.com/vbespalk/wolf3d/blob/master/wolf3d.en.pdf)

## Screenshots

![alt tag](https://github.com/vbespalk/wolf3d/blob/master/screenshots/screenshot.jpg)

## Features

- move in any directions (sideways movements included)
- rotation with keys (inc. look up/down illusion)
- textured wall
- floor casting
- skybox
- walls collision (with an slight realistic offset)
- sound effects
- FPS Monitor
- auto regulated FPS (~60 fps)
- bunch of maps (i.e. levels)
- simple ambient occlusion
- multithreading (SDL threds)
- possible to build on MacOS, Linux
- modifiable map:
  - 0 - free space
  - 1-3 - texture modes for walls

## Install & launch

```
https://github.com/vbespalk/wolf3d.git ~/wolf3d
cd ~/wolf3d && make
./wolf3d maps/basic00
./wolf3d maps/basic01
```
```
To build on Linux be sure you have installed following packages on your machine:
-SDL2 
-SDL2_image
-SDL2_mixer
-SDL2-ttf
```

## Commands & shortcuts

- arrows - rotate (up/down/left/right)
- w/s - forth/back movements
- a/s - left/right side movements
- r - reset all the changes made
- -/= to adjust volume (standard keyboard)
- esc - quit

## GIF Exploring the maze (low quality)

![alt tag](https://github.com/vbespalk/wolf3d/blob/master/screenshots/wolf.gif)
