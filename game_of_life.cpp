//
//  game_of_life.cpp
//  gpucompute
//

#include <Metal/Metal.hpp>
#include "game_of_life.h"

void game_of_life(int *cells_inout, const int points_count)
{
    NS::AutoreleasePool *pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    
    MTL::Device *pDevice = MTL::CreateSystemDefaultDevice();
    
    NS::Error* pError = nullptr;
    NS::URL *fileURL = NS::URL::fileURLWithPath(NS::String::string("/usr/local/lib/gpucompute.metallib", NS::UTF8StringEncoding));
    
    MTL::Library *pLibrary = pDevice->newLibrary(fileURL, &pError);
    assert(pLibrary);
    
    MTL::Function *pGameOfLifeFunction = pLibrary->newFunction(NS::String::string("game_of_life_kernel", NS::UTF8StringEncoding));
    assert(pLibrary);
    
    MTL::ComputePipelineState *pGameOfLifeFunctionPSO = pDevice->newComputePipelineState(pGameOfLifeFunction, &pError);
    assert(pGameOfLifeFunctionPSO);
    
    pGameOfLifeFunction->release();
    pLibrary->release();
    
    size_t cells_size = sizeof(int) * points_count * points_count;
    
    MTL::Buffer *pCellsIn = pDevice->newBuffer(cells_size, MTL::ResourceStorageModeShared);
    MTL::Buffer *pCellsOut = pDevice->newBuffer(cells_size, MTL::ResourceStorageModeShared);
    
    int *pCellsInContents = reinterpret_cast<int *>(pCellsIn->contents());
    memcpy(pCellsInContents, cells_inout, cells_size);
    
    MTL::CommandQueue *pCommandQueue = pDevice->newCommandQueue();
    MTL::CommandBuffer *pCommandBuffer = pCommandQueue->commandBuffer();
    assert(pCommandBuffer);
    
    MTL::ComputeCommandEncoder *pComputeEncoder = pCommandBuffer->computeCommandEncoder();
    assert(pComputeEncoder);
    
    pComputeEncoder->setComputePipelineState(pGameOfLifeFunctionPSO);
    pComputeEncoder->setBuffer(pCellsIn, 0, 0);
    pComputeEncoder->setBuffer(pCellsOut, 0, 1);
    
    MTL::Size gridSize = MTL::Size(points_count, points_count, 1);
    MTL::Size threadgroupSize = MTL::Size(32, 32, 1);
    
    pComputeEncoder->dispatchThreads(gridSize, threadgroupSize);
    
    pComputeEncoder->endEncoding();
    
    pCommandBuffer->commit();
    pCommandBuffer->waitUntilCompleted();
    
    memcpy(cells_inout, reinterpret_cast<int *>(pCellsOut->contents()), cells_size);
    
    pAutoreleasePool->release();
    
    pCommandQueue->release();
    
    pCellsIn->release();
    pCellsOut->release();
    
    pGameOfLifeFunctionPSO->release();
    pDevice->release();
}
