Access Apple’s Metal from Python or C or C++
============================================
This project demonstrates how Metal and thus the GPU can be accessed from Python, C, and C++ for compute tasks by accessing a Metal kernel via a basic C++ library with a C interface.

We compute a Mandelbrot subset and visualize it using Python.

Setup
-----
1. Open the Xcode project file.
2. Select the menu item `Product > Build` to create the libraries.
3. Select the menu item `Product > Copy Build Folder Path`.
4. Open Terminal and type `cd `. Append the build path by pasting it into Terminal. Type `cd Products/Debug` to enter the folder where the libraries have been created.
5. Type `sudo cp gpucompute.metallib libgpucompute.dylib /usr/local/lib` to install the libraries.
6. Copy the file `mandelbrot_set.py` to a folder where you want to run it with Python. You must have NumPy and Matplotlib installed. Copy `libgpucompute.dylib` into the same folder. This is required because of restrictions with `dlopen()`.
7. Run `mandelbrot_set.py` with Python3 and you should see an image of the Mandelbrot set.
