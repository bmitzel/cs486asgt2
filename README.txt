 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * Assignment: 2 - Picking
 * Due Date: 9/29/2014
 
picking.cpp is a C++ program which implements a basic
OpenGL renderer. The renderer is capable of drawing a ground
plane, a sky box, and 3 PLY models. Using keyboard input,
the renderer can toggle between using a GLSL shader program
or the OpenGL fixed function pipeline. Also, it can toggle
on or off the drawing of the models' bounding volumes.
Finally, a user's mouse click on a model will toggle on or
off the drawing of that model's bounding volume.

------------------------------------------------------------
	
Features:

The following hotkeys are available:
	b - toggle rendering the bounding volumes
	f - toggle full screen mode (freeglut only)
	g - toggle between the GLSL program and the fixed
	    function pipeline
	o - reset the window to its original resolution
	ESC or q - quit the program
	h - print a help message
	
Clicking the mouse on a model in the scene toggles on or off
the drawing of that model's bounding sphere.

------------------------------------------------------------

Completed:

All of the requirements for this assignment have been
completed, including:
	1. Render a scene with 3 smoothly shaded geometric
	   models
	2. All 3 of the models are stored in PLY format
	3. The model data is stored in a linear, linked data
	   structure
	4. Each object in the scene is bounded by a bounding
	   sphere
	5. The scene includes a shaded ground plane and shaded
	   sky box
	6. The entire scene is visible from the default camera
	   position
	7. There is an interior point light source which
	   illuminates the scene
	8. The shading is accomplished using the Blinn-Phong
	   GLSL shader program
	9. The keyboard interface is fully functional as
	   described in the Features section above
   10. Picking via ray-sphere intersection is fully
       functional

------------------------------------------------------------
       
Bugs:

There are currently no known bugs or limitations.

------------------------------------------------------------

Building:

Using OSX, Linux, or the FreeBSD VM distributed by Professor
Michael Shafae, open a terminal window to the source
directory and enter the following command at the shell
prompt:

	make

or:

	gmake

------------------------------------------------------------
	
Executing:

From the same directory where you built the executable,
enter the command:

	./picking [<window_width> <window_height>]
		window_width: The optional width of the window
		window_height: The optional height of the window
		
The window width and height default to 1280 x 720 if
excluded from the command line.
