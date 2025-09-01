Access Apple’s Metal from Python or C or C++
============================================
This project demonstrates how Metal and thus the GPU can be accessed from Python, C and C++ for compute tasks by accessing a Metal kernel via a basic C++ library with a C interface.

We compute a Mandelbrot subset and visualize it using Python. Another demonstration shows similarly an animation of Conway’s Game of Life.

Setup
-----
1. Open Terminal and clone the repository.
2. Change into the thus created directory `PyCMetal`.
3. Type `make` to build the libraries.
4. Type `make install` to install the libraries in the directory `/usr/local/lib`.
5. Copy the files `mandelbrot_set.py` and `game_of_life.py` to a directory where you want to run them with Python. You must have NumPy and Matplotlib installed. (You can install these using a virtual environment by typing `python3 -m venv .venv; source .venv/bin/activate; pip3 install numpy; pip3 install matplotlib` after changing into the directory.)
6. Copy the dynamic library from `/usr/local/lib/libgpucompute.dylib` to the same directory. This is required because of restrictions governing `dlopen()`.
7. Run `mandelbrot_set.py` and `game_of_life.py` with Python 3 and you should see a visualization of the Mandelbrot set and an animation of the Game of Life respectively.
8. Optionally type `make clean` in the `PyCMetal` directory to remove the `build` directory.
