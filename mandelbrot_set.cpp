//
//  mandelbrot_set.cpp
//  gpucompute
//

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.hpp>
#include "mandelbrot_set.h"

void mandelbrot_set(const float *points, float *mandelbrot_subset, const struct params *p)
{
    NS::AutoreleasePool *pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    
    MTL::Device *pDevice = MTL::CreateSystemDefaultDevice();
    
    NS::Error* pError = nullptr;
    NS::URL *fileURL = NS::URL::fileURLWithPath(NS::String::string("/usr/local/lib/gpucompute.metallib", NS::UTF8StringEncoding));
    
    MTL::Library *pLibrary = pDevice->newLibrary(fileURL, &pError);
    assert(pLibrary);
    
    MTL::Function *pMandelbrotFunction = pLibrary->newFunction(NS::String::string("mandelbrot_set_kernel", NS::UTF8StringEncoding));
    assert(pLibrary);
    
    MTL::ComputePipelineState *pMandelbrotFunctionPSO = pDevice->newComputePipelineState(pMandelbrotFunction, &pError);
    assert(pMandelbrotFunctionPSO);
    
    pMandelbrotFunction->release();
    pLibrary->release();
    
    int points_size = sizeof(float) * p->points_count;
    int subset_size = sizeof(float) * p->points_count * p->points_count;
    
    MTL::Buffer *pPoints = pDevice->newBuffer(points_size, MTL::ResourceStorageModeShared);
    MTL::Buffer *pMandelbrotSubset = pDevice->newBuffer(subset_size, MTL::ResourceStorageModeShared);
    MTL::Buffer *pParams = pDevice->newBuffer(sizeof(struct params), MTL::ResourceStorageModeShared);
    
    float *pPointsContents = reinterpret_cast<float *>(pPoints->contents());
    memcpy(pPointsContents, points, points_size);
    
    struct params *pParamsContents = reinterpret_cast<struct params *>(pParams->contents());
    *pParamsContents = *p;
    
    MTL::CommandQueue *pCommandQueue = pDevice->newCommandQueue();
    MTL::CommandBuffer *pCommandBuffer = pCommandQueue->commandBuffer();
    assert(pCommandBuffer);
    
    MTL::ComputeCommandEncoder *pComputeEncoder = pCommandBuffer->computeCommandEncoder();
    assert(pComputeEncoder);
    
    pComputeEncoder->setComputePipelineState(pMandelbrotFunctionPSO);
    pComputeEncoder->setBuffer(pPoints, 0, 0);
    pComputeEncoder->setBuffer(pMandelbrotSubset, 0, 1);
    pComputeEncoder->setBuffer(pParams, 0, 2);
    
    MTL::Size gridSize = MTL::Size(p->points_count * p->points_count, 1, 1);
    MTL::Size threadgroupSize = MTL::Size(pMandelbrotFunctionPSO->maxTotalThreadsPerThreadgroup(), 1, 1);
    
    pComputeEncoder->dispatchThreads(gridSize, threadgroupSize);
    
    pComputeEncoder->endEncoding();
    
    pCommandBuffer->commit();
    pCommandBuffer->waitUntilCompleted();
    
    memcpy(mandelbrot_subset, reinterpret_cast<float *>(pMandelbrotSubset->contents()), subset_size);
    
    pAutoreleasePool->release();
    
    pCommandQueue->release();
    
    pPoints->release();
    pMandelbrotSubset->release();
    pParams->release();
    
    pMandelbrotFunctionPSO->release();
    pDevice->release();
}
