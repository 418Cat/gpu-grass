# GPU Grass
A small shell texturing grass implementation, based on [Acerola's video about fur/grass rendering](https://www.youtube.com/watch?v=9dr-tRQzij4).
Written in C++ using OpenGL
___
## How
The only geometry in the scene is a single flat plane:
![Plane](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/uv.png)

The plane is then subdivided in multiple square sections:
![Subdivided plane](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/uv_squares.png)

Each section is assigned a random number between 0 and 1 based on the square's x&y coordinates:
![Random squares](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/squares_random.png)

The plane is drawn multiple times at different heights. Each square section is drawn only if the height is less than the random number assigned to it:
![Discarded random squares](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/squares_random_discarded.png)

By shading the square based on its height, it gives it a nice grass-like look:
![Green squares](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/squares_shaded.png)

___
## Misc
The camera moves with WASD/ZQSD and can be rotated by clicking&dragging the mouse.
Imgui is used to allow changing parameters during runtime
___
## Credits
The hash function used to generate random numbers for the height was made by David Hoskins:
https://www.shadertoy.com/view/4djSRW
___
## Pictures
![Square grass](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/square.png)

![Round grass](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/round.png)

![Round dense grass](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/round_dense.png)

![Pointy grass 0](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/pointy_0.png)

![Pointy grass 1](https://raw.githubusercontent.com/418Cat/gpu-grass/refs/heads/main/images/pointy_1.png)
___
This code is under the MIT license