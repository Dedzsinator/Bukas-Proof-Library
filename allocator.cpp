#include <iostream>
#include <limits>
#include <memory>
#include <vector>

template <typename T>
class MemoryPoolAllocator {
public:
    using value_type = T;
    
    // Constructor and destructor
    MemoryPoolAllocator() : memoryPool(nullptr), poolSize(0), poolIndex(0) {}
    ~MemoryPoolAllocator() { delete[] memoryPool; }

    // Allocate memory
    T* allocate(std::size_t n) {
        if (memoryPool == nullptr || poolIndex + n > poolSize) {
            allocateNewPool(n);
        }
        
        T* result = memoryPool + poolIndex;
        poolIndex += n;
        return result;
    }

    // Deallocate memory
    void deallocate(T* ptr, std::size_t n) {
        // Memory pooling - no need to deallocate individual elements
        // Actual deallocation happens when the pool is destroyed
    }

    // Construct and destroy objects in-place
    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args) {
        new(ptr) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }

    // Allocator trait functions
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    // Max size of allocations
    std::size_t max_size() const noexcept {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

private:
    T* memoryPool;
    std::size_t poolSize;
    std::size_t poolIndex;

    void allocateNewPool(std::size_t n) {
        poolSize = std::max(poolSize * 2, n);
        memoryPool = new T[poolSize];
        poolIndex = 0;
    }
};

// Rebind mechanism
template <typename T, typename U>
bool operator==(const MemoryPoolAllocator<T>&, const MemoryPoolAllocator<U>&) {
    return true;
}

template <typename T, typename U>
bool operator!=(const MemoryPoolAllocator<T>&, const MemoryPoolAllocator<U>&) {
    return false;
}

int main() {
    // Use with STL containers
    std::vector<int, MemoryPoolAllocator<int>> vec;
    vec.push_back(10);
    vec.push_back(20);

    std::cout << "Vector contains: ";
    for (auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
