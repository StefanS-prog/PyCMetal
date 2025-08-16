Access Apple’s Metal from Python or C or C++
============================================
This project demonstrates how Metal and thus the GPU can be accessed from Python, C, and C++ for compute tasks by accessing a Metal kernel via a basic C++ library with a C interface.

We compute a Mandelbrot subset and visualize it using Python.

Setup
-----
1. Clone the repository.
2. Open Terminal and change into the directory `PyCMetal` which has been created for the repository.
3. Type `make` to build the libraries.
4. Type `make install` to install the libraries in `/usr/local/lib`.
5. Copy the file `mandelbrot_set.py` to a directory where you want to run it with Python. You must have NumPy and Matplotlib installed. Copy the dynamic library from `/usr/local/lib/libgpucompute.dylib` to the same directory. This is required because of restrictions with `dlopen()`.
6. Run `mandelbrot_set.py` with Python 3 and you should see an image of the Mandelbrot set.
7. Optionally type `make clean` in the `PyCMetal` directory.
