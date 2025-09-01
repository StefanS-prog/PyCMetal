from matplotlib import pyplot as plt
import matplotlib.animation as animation
import numpy as np
from ctypes import *

gpucompute_dll = CDLL("./libgpucompute.dylib")
game_of_life_fn = gpucompute_dll.game_of_life
game_of_life_fn.argtypes = [POINTER(c_int), c_int]

def update_cells(frame, img, cells, points_count):
    game_of_life_fn(cells.ctypes.data_as(POINTER(c_int)), points_count)
    img.set_data(cells)

    return img

points_count = 256
rng = np.random.default_rng()
cells = np.int32(rng.choice([1, 0], size=(points_count, points_count), p=[0.25, 0.75]))

fig = plt.figure("Game of Life")
original_size = fig.get_size_inches()
fig.set_size_inches(original_size * 2)
img = plt.imshow(cells, interpolation="none")
anim = animation.FuncAnimation(fig, update_cells, fargs=(img, cells, points_count), interval=100, frames=10000)
plt.show()
