//
//  kernels.metal
//  gpucompute
//

#include <metal_stdlib>

using namespace metal;

struct params
{
    int max_iterations;
    int points_count;
};

[[kernel]] void mandelbrot_set_kernel(constant float *points, device float *mandelbrot_subset, constant struct params *p, uint t_id [[thread_position_in_grid]])
{
    int x = t_id % p->points_count;
    int y = p->points_count - 1 - t_id / p->points_count;
    
    float c_re = points[x];
    float c_im = points[y];
    
    float2 z = float2(0.0f, 0.0f);
    float temp_re;

    mandelbrot_subset[t_id] = 1.0f;
    
    for (int k = 0; k < p->max_iterations; k++)
    {
        temp_re = z.x * z.x - z.y * z.y + c_re;
        z.y = 2 * z.x * z.y + c_im;
        z.x = temp_re;
        
        if (length_squared(z) > 4.0f)
        {
            mandelbrot_subset[t_id] = 0.0f;
            
            break;
        }
    }
}
