//
//  mandelbrot_set.h
//  gpucompute
//

#ifndef mandelbrot_set_h
#define mandelbrot_set_h

struct params
{
    int max_iterations;
    int points_count;
};

extern "C" void mandelbrot_set(const float *points, float *mandelbrot_subset, const struct params *p);

#endif /* mandelbrot_set_h */
