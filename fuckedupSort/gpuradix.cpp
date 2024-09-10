#include <iostream>
#include <cuda.h>

#define BLOCK_SIZE 1024  // Number of threads per block

__global__ void countKernel(unsigned int* input, unsigned int* output, int bit, int size) {
    __shared__ unsigned int count[2 * BLOCK_SIZE];  // shared memory for counting 0's and 1's

    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int tidLocal = threadIdx.x;
    
    // Initialize the shared memory
    count[tidLocal] = 0;
    count[BLOCK_SIZE + tidLocal] = 0;
    
    __syncthreads();
    
    // For all elements within the bounds
    if (tid < size) {
        unsigned int value = input[tid];
        int bitValue = (value >> bit) & 1;
        atomicAdd(&count[BLOCK_SIZE * bitValue + tidLocal], 1);  // Count 0's or 1's based on bit
    }
    
    __syncthreads();
    
    // Prefix sum on shared memory (exclusive scan)
    for (int offset = 1; offset < BLOCK_SIZE; offset *= 2) {
        int temp = count[tidLocal];
        __syncthreads();
        
        if (tidLocal >= offset)
            count[tidLocal] += count[tidLocal - offset];
        
        __syncthreads();
    }
    
    // Output the sorted elements
    if (tid < size) {
        unsigned int value = input[tid];
        int bitValue = (value >> bit) & 1;
        int pos = count[BLOCK_SIZE * bitValue + tidLocal] - 1;
        output[pos] = value;
    }
}

__global__ void moveKernel(unsigned int* input, unsigned int* output, int bit, int size) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < size) {
        unsigned int value = input[tid];
        int bitValue = (value >> bit) & 1;
        output[tid] = value;
    }
}

void parallelRadixSort(unsigned int* h_input, int size) {
    unsigned int* d_input;
    unsigned int* d_output;

    // Allocate memory on device
    cudaMalloc((void**)&d_input, size * sizeof(unsigned int));
    cudaMalloc((void**)&d_output, size * sizeof(unsigned int));

    cudaMemcpy(d_input, h_input, size * sizeof(unsigned int), cudaMemcpyHostToDevice);

    int numBlocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Iterate over bits
    for (int bit = 0; bit < 32; ++bit) {
        // Count 0's and 1's for each bit
        countKernel<<<numBlocks, BLOCK_SIZE>>>(d_input, d_output, bit, size);
        cudaDeviceSynchronize();
        // Move the sorted elements to the output
        moveKernel<<<numBlocks, BLOCK_SIZE>>>(d_output, d_input, bit, size);
        cudaDeviceSynchronize();
    }

    // Copy back the sorted array to host
    cudaMemcpy(h_input, d_input, size * sizeof(unsigned int), cudaMemcpyDeviceToHost);

    cudaFree(d_input);
    cudaFree(d_output);
}

int main() {
    const int size = 1024;
    unsigned int h_input[size];
    
    // Fill the input array with random values
    for (int i = 0; i < size; ++i) {
        h_input[i] = rand() % 1000;
    }

    // Perform the parallel radix sort
    parallelRadixSort(h_input, size);

    // Print the sorted array
    for (int i = 0; i < size; ++i) {
        std::cout << h_input[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

//! compile with: nvcc radix_sort.cu -o radix_sort