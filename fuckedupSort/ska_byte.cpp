#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

struct PartitionInfo
{
    PartitionInfo()
        : count(0)
    {
    }
 
    union
    {
        size_t count;
        size_t offset;
    };
    size_t next_offset;
};

// Function to unroll a loop four times
template<typename It, typename Func>
void unroll_loop_four_times(It begin, size_t count, Func func) {
    size_t i = 0;
    for (; i + 4 <= count; i += 4) {
        func(begin + i);
        func(begin + i + 1);
        func(begin + i + 2);
        func(begin + i + 3);
    }
    for (; i < count; ++i) {
        func(begin + i);
    }
}

// Custom partition function
template<typename It, typename Pred>
It custom_std_partition(It begin, It end, Pred pred) {
    It middle = std::partition(begin, end, pred);
    return middle;
}

// Extract key algorithm
template<typename It, typename ExtractKey>
void ska_byte_sort(It begin, It end, ExtractKey && extract_key)
{
    PartitionInfo partitions[256];
    for (It it = begin; it != end; ++it)
    {
        ++partitions[extract_key(*it)].count;
    }
    uint8_t remaining_partitions[256];
    size_t total = 0;
    int num_partitions = 0;
    for (int i = 0; i < 256; ++i)
    {
        size_t count = partitions[i].count;
        if (count)
        {
            partitions[i].offset = total;
            total += count;
            remaining_partitions[num_partitions] = i;
            ++num_partitions;
        }
        partitions[i].next_offset = total;
    }
    for (uint8_t * last_remaining = remaining_partitions + num_partitions, * end_partition = remaining_partitions + 1; last_remaining > end_partition;)
    {
        last_remaining = custom_std_partition(remaining_partitions, last_remaining, [&](uint8_t partition)
        {
            size_t & begin_offset = partitions[partition].offset;
            size_t & end_offset = partitions[partition].next_offset;
            if (begin_offset == end_offset)
                return false;
 
            unroll_loop_four_times(begin + begin_offset, end_offset - begin_offset, [partitions = partitions, begin, &extract_key](It it)
            {
                uint8_t this_partition = extract_key(*it);
                size_t offset = partitions[this_partition].offset++;
                std::iter_swap(it, begin + offset);
            });
            return begin_offset != end_offset;
        });
    }
}

int main() {
    const int N = 100000000;

    vector<uint8_t> data(N); // Allocate the required size

    generate(data.begin(), data.end(), []() { return rand() % 256; });

    auto start = chrono::high_resolution_clock::now();

    ska_byte_sort(data.begin(), data.end(), [](uint8_t x) { return x; });

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> diff = end - start;

    cout << "Time taken: " << diff.count() << " s\n";
    cout << "Is sorted: " << (is_sorted(data.begin(), data.end()) ? "\033[1;32m[Yes]\033[0m" : "\033[1;31m[No]\033[0m") << endl;

    return 0;
}