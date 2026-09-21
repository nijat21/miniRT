_This project has been created as part of the 42 curriculum by abraz-ab and nismayil_ 

# miniRT

## Description

miniRT is a C-based raytracer created to render simple 3D scenes defined in a custom .rt file format. This project reads a scene description, validates it, and renders the result in a window using the MinilibX graphics library.

The implementation includes the core components of a basic renderer:
- parsing of scene elements such as ambient light, camera, light, spheres, planes, and cylinders
- vector and ray math for perspective projection and intersection tests
- nearest-hit selection for visible objects
- basic lighting and shading based on the scene light source
- image generation and display in a graphical window

The goal of this project is to apply the main ideas behind ray tracing in a compact, manually implemented setup instead of using a higher-level rendering engine.

## Rendering pipeline

At a high level, the renderer works like this:

### 1. Viewport

The camera has a field of view and a virtual screen, called the viewport. Each pixel on the screen is mapped to a point on this viewport, and the program converts each pixel position into a 3D sample point in front of the camera.

In practice, the viewport is built from the camera's horizontal field of view and the image resolution. The code computes a per-pixel offset in camera space and then translates that into world space. This means every pixel corresponds to one viewing ray directed through the scene.

### 2. Camera right and up vectors

The project stores the camera as an origin plus a normal direction. From that direction, it builds a local basis:

- the camera normal is the forward vector
- the right vector is perpendicular to the forward direction and to the world-up direction
- the up vector is derived from the right vector and the forward direction

This makes the camera orientation stable even when the camera is not aligned to the global axes. Each viewport point is then offset by a combination of right and up, so the ray direction points from the camera origin through the correct location on the virtual screen.

### 3. Primary rays and shadow rays

For each pixel, the program creates a primary ray:

- origin = camera position
- direction = normalized vector from camera origin to the corresponding viewport point

The scene is tested against this ray to find the closest visible object. Once a hit point is found, the code computes the surface normal and then creates a shadow ray from the hit position toward the light source.

This shadow ray is used to answer a simple question: is anything between the hit point and the light, blocking the illumination? If an intersection occurs before the light is reached, that point is in shadow and the light contribution is ignored for that sample.

### 4. Coloring logic

The final color is based on a simple local lighting model:

- ambient lighting: a constant background contribution based on the ambient light ratio and color
- diffuse lighting: the surface color is scaled by the light brightness and by the cosine of the angle between the surface normal and the light direction
- shadowing: if the point is occluded by another object, only the ambient term remains

The project also offsets the hit point slightly along the surface normal before testing the shadow ray. This avoids self-intersection artifacts, where the surface accidentally blocks its own light.

In code terms, the render loop calls the ray generator for every pixel, finds the nearest hit, evaluates shadow visibility, and converts the final floating-point color to RGB bytes for display in the window.

## Instructions

1. Compile the project from the repository root:
   make

2. Run the program with a valid scene file:
   ./minirt maps/valid/<scene_file>.rt

3. The program expects exactly one .rt file as input. It validates required scene elements such as ambient light, camera, and light before rendering.

4. Example scene files are available in the maps/valid directory.

5. To clean build artifacts:
   make clean

6. To rebuild everything from scratch:
   make re

## Resources

- https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
- https://www.youtube.com/watch?v=6VHpZYTHZG4
- https://docs.gl/

AI was used for understanding math concepts and testing support.
