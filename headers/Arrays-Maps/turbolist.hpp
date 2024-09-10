#pragma once

#include <cstdint>
#include <cstdlib>
#include <cassert>

#ifndef TL_NOINLINE
#define TL_NOINLINE __attribute__((noinline))
#endif

#ifndef TL_LIKELY
#define TL_LIKELY(x) __builtin_expect(!!(x), 1)
#endif
#ifndef TL_UNLIKELY
#define TL_UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

typedef void*(MallocLike)(size_t);
typedef void(FreeLike)(void*);

template<typename T, MallocLike MALLOC = malloc, FreeLike FREE = free>
class TurboList {
    T *old;
    T *next;

    uint32_t mid;
    uint32_t end;

    uint32_t capacity;

    TL_NOINLINE void grow_and_insert(T elem) noexcept {
        // asser(mid == 0);
        if(old) FREE(old);
        old = next;
        mid = end;
        capacity *= 2;
        nexzt = (int *)MALLOC(this->capacity * sizeof(T));
        
        insert(elem);
    }

public:
    inline TurboList(uint32_t initial_size = 0, uint32_t initial_cap = 16) noexcept :
        old(nullptr),
        mid(0),
        end(initial_cap) {
    
            next = (int *) MALLOC(initial_cap * sizeof(T));
        }

    inline ~TurboList() noexcept {

        if(old) FREE(old);
        if(next) FREE(next);
    }

    inline T& operator[](uint32_t i) noexcept {
        return i < mid ? old[i] : next[i];
    }

    inline void iterate(void(callback)(T&)) noexcept {
        //old
        for(uint32_t i = 0; i < mid; ++i) {
            callback(old[i]);
        }

        //next
        for(uint32_t i = mid; i < end; ++i) {
            callback(next[i]);
        }
    }

    inline void inser(T elem) noexcept {
        if(TL_LIKELY(end < capacity)) {
            bool hasmid = mid > 0;
            mid -= hasmid;

            next[mid] = hasmid ? old[mid] : next[mid];

            next[end++] = elem;
        } else {
            //grow
            grow_and_insert(elem);
        }
    }

    inline uint32_t size() noexcept {
        return mid + (capacity - end - 1);
    }
};