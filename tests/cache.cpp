#include <iostream>
#include <vector>
#include <optional>
#include <immintrin.h> // For potential SIMD optimizations
#include <xmmintrin.h> // For cache-line prefetching
#include <chrono>
#include <iomanip>

template <typename T, std::size_t Size>
class CircularBuffer {
private:
    alignas(64) T buffer[Size];  // Align buffer to cache line size
    std::size_t head = 0;
    std::size_t tail = 0;
    bool full = false;

public:
    CircularBuffer() {
        static_assert((Size & (Size - 1)) == 0, "Size must be a power of 2 for optimal performance.");
    }

    // Insertion with inlining to reduce function call overhead
    inline void put(const T& item) {
        buffer[head] = item;

        // Use branchless logic to update head and tail
        head = (head + 1) & (Size - 1);  // Fast modulo using bitwise AND

        if (full) {
            tail = (tail + 1) & (Size - 1);  // Overwrite the oldest element
        }

        full = (head == tail);
    }

    // Retrieval with inlining to reduce function call overhead
    inline std::optional<T> get() {
        if (isEmpty()) {
            return std::nullopt;  // Return empty optional if buffer is empty
        }

        T item = buffer[tail];
        full = false;
        tail = (tail + 1) & (Size - 1);  // Fast modulo using bitwise AND

        return item;
    }

    // Cache-line prefetching
    void prefetchNext() const {
        _mm_prefetch(reinterpret_cast<const char*>(&buffer[head]), _MM_HINT_T0);
    }

    // Check if the buffer is empty
    inline bool isEmpty() const {
        return (!full && (head == tail));
    }

    // Check if the buffer is full
    inline bool isFull() const {
        return full;
    }

    // Get the current size of the buffer
    std::size_t size() const {
        if (full) {
            return Size;
        }
        return (head >= tail) ? (head - tail) : (Size + head - tail);
    }

    // Batch insertions to optimize memory access patterns
    void putBatch(const std::vector<T>& items) {
        for (const auto& item : items) {
            put(item);
        }
    }

    // Batch retrievals to minimize overhead
    std::vector<T> getBatch(std::size_t count) {
        std::vector<T> results;
        results.reserve(count);

        for (std::size_t i = 0; i < count && !isEmpty(); ++i) {
            if (auto item = get()) {
                results.push_back(*item);
            }
        }

        return results;
    }
};

// Benchmarking Function
template <typename Func>
double benchmark(Func&& func, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    constexpr int bufferSize = 16384;
    constexpr int numOps = 5000000;

    // Circular Buffer Benchmark
    CircularBuffer<int, bufferSize> circBuffer;
    double circularInsertTime = benchmark([&]() {
        circBuffer.put(rand());
    }, numOps);

    double circularRetrieveTime = benchmark([&]() {
        circBuffer.get();
    }, numOps);

    std::cout << "Circular Buffer Insertion Time: " << std::fixed << std::setprecision(9) << circularInsertTime << " seconds\n";
    std::cout << "Circular Buffer Retrieval Time: " << std::fixed << std::setprecision(9) << circularRetrieveTime << " seconds\n";

    return 0;
}
