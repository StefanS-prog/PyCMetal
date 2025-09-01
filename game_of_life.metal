//
//  game_of_life.metal
//  gpucompute
//

#include <metal_stdlib>

using namespace metal;

#define INDEX(_x, _y) ((_x) + (_y) * grid_size.x)

[[kernel]] void game_of_life_kernel(constant int *cells_in, device int *cells_out, uint2 pos [[thread_position_in_grid]], uint2 grid_size [[threads_per_grid]])
{
    const int left_x = pos.x == 0 ? grid_size.x - 1 : pos.x - 1;
    const int right_x = pos.x == grid_size.x - 1 ? 0 : pos.x + 1;
    
    const int up_y = pos.y == 0 ? grid_size.y - 1 : pos.y - 1;
    const int down_y = pos.y == grid_size.y - 1 ? 0 : pos.y + 1;
    
    const int neighbours_count =
        cells_in[INDEX(left_x, up_y)] +
        cells_in[INDEX(left_x, pos.y)] +
        cells_in[INDEX(left_x, down_y)] +
        cells_in[INDEX(pos.x, up_y)] +
        cells_in[INDEX(pos.x, down_y)] +
        cells_in[INDEX(right_x, up_y)] +
        cells_in[INDEX(right_x, pos.y)] +
        cells_in[INDEX(right_x, down_y)];
    
    if (cells_in[INDEX(pos.x, pos.y)] == 1)
    {
        if (neighbours_count == 2 || neighbours_count == 3)
            cells_out[INDEX(pos.x, pos.y)] = 1;
        else
            cells_out[INDEX(pos.x, pos.y)] = 0;
    }
    else if (cells_in[INDEX(pos.x, pos.y)] == 0)
    {
        if (neighbours_count == 3)
            cells_out[INDEX(pos.x, pos.y)] = 1;
        else
            cells_out[INDEX(pos.x, pos.y)] = 0;
    }
}
