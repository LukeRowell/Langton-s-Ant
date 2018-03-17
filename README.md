# Langton's Ant
A simulation of Langton's Ant using SFML in C++.

Langton's Ant is a two-dimensional universal Turing machine invented by Chris Langton in 1986. Langton's Ant is part of a broader classification of Turing machines known as turmites. Turmites are simply Turing machines which have an orientation, a state, and a tape which consists of cells on a two-dimensional grid.

Langton's Ant is defined by these rules:

	1. If the ant is on a white square: flip the color of the square, turn right, and move forward one cell
	2. If the ant is on a black square: flip the color of the square, turn left, and move forward one cell
  
Although the rules are few and also simple, they produce very interesting patterns.

This simulation of Langton's Ant runs on an 5000x5000 (scaled down to 1000x1000 to fit on the screen nicely) pixel grid which treats each pixel as a cell. On top of having the normal black and white view, there is also a heat map view of the simulation. The heat map view (which is toggled on with the 'h' key) allows you to see how frequently each cell in the grid has been visited by the ant. The colors in order of least visited to most visited are blue, cyan, green, yellow, and red.

The controls for the program are as follows:

	h 	-    toggles the heat map view on/off
	
	space 	-    toggles the use of the thread on/off (speed increase)
