from time import time
from matplotlib import pyplot as plt
import numpy as np
from ctypes import *
import sys

gpucompute_dll = CDLL("./libgpucompute.dylib")
mandelbrot_set_fn = gpucompute_dll.mandelbrot_set

class params(Structure):
    _fields_ = [
        ("max_iterations", c_int),
        ("points_count", c_int)
    ]

mandelbrot_set_fn.argtypes = [POINTER(c_float), POINTER(c_float), POINTER(params)]

def mandelbrot_set(points_count, max_iterations):
    points = np.linspace(-2, 2, points_count, dtype=np.float32)
    mandelbrot_subset = np.empty(shape=(points.size, points.size), dtype=np.float32)
    params_i = params(max_iterations, points.size)
    mandelbrot_set_fn(points.ctypes.data_as(POINTER(c_float)), mandelbrot_subset.ctypes.data_as(POINTER(c_float)), byref(params_i))

    return mandelbrot_subset

t1 = time()
mandelbrot_subset = mandelbrot_set(512, 256)
t2 = time()
duration = t2 - t1
print(f"Calculation duration: {duration:.3f} s")

fig = plt.figure("Mandelbrot Set")
original_size = fig.get_size_inches()
fig.set_size_inches(original_size * 2)
plt.imshow(mandelbrot_subset, extent=(-2, 2, -2, 2), interpolation="none")
plt.show()
