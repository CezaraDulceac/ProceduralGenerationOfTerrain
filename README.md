# ProceduralGenerationOfTerrain

In Game.h is the main logic of the project.

The project will display a terrain made from meshes that can be edited and modeled after the users' preferences.

The logic of the program goes like this:
The user can set the dimensions of the terrain after their needs
There will be two possibilities to modify the terrain:
    1. Using Perlin Noise alghoritm for a pseudo-random generation - the parameters for that alghoritm can be changed aswell
    2. Starting from a plain terrain 

The program provides a series of options for the terrain modificatons:
1. There is a brush with which the user can change the elevation of the terrain (up or down)
    *there is a possibily to change the depth of the brush and also the size of the affected terrain surface that can be modified
2. There are predifined brushes that can instantly modify the surface with specific landforms (water level, grass level, hill, mountain)
3. There is the possibility to add texture based on the elevation of terrain - starting from water - sand - grass - etc.
4. The textures can be predefined or custom added in the project by the user
5. The whole terrain can also be exported from the project or imported in case of reworking need to be done.
6. On all stages of generation the user can move around on the scene using mouse and ASDW keys from keyboard.

In ScreenShots folder I added a series of pics with the program.


