#ifndef TURBO_LIST_H
#define TURBO_LIST_H

#include<stdint.h>
#include<stdlib.h>
#include<assert.h>

#ifndef TL_NOINLINE
#define TL_NOINLINE __attribute__((noinline))
#endif

#ifndef TL_LIKELY
#define TL_LIKELY(x) __builtin_expect(!!(x), 1)
#endif
#ifndef TL_UNLIKELY
#define TL_UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

struct turbolist {
    int *old;
    int *next;

    uint32_t mid;
    uint32_t end;

    uint32_t capacity;
    void* (*malloc)(size_t size);
    void (*free)(void*);
};

typedef struct turbolist turbolist;

static inline void turbolist_insert(turbolist *tl, int elem);

static TL_NOINLINE void __turbolist_grow_and_insert(turbolist *tl, int elem) {
    // assert(mid == 0);
    if(tl->old) tl->free(tl->old);
    tl->old = tl->next;
    tl->mid = tl->end;
    tl->capacity *= 2;
    tl->next = (int *)tl->malloc(tl->capacity * sizeof(int));
    
    turbolist_insert(tl, elem);
}

static inline turbolist turbolist_create_adv(void* (*malloc_like)(size_t size), void (*free_like)(void*), uint32_t initial_size, uint32_t initial_cap) {
    assert(initial_size <= initial_cap);

    turbolist tl;
    tl.old = NULL;
    tl.mid = 0;
    tl.end = 16;
    tl.capacity = 16;
    tl.malloc = malloc_like;
    tl.free = free_like;
    tl.next = (int *) tl.malloc(tl.capacity * sizeof(int));
    return tl;
}

#ifndef MP_CSTDLIB
static inline turbolist turbolist_create() {
    return turbolist_create_adv(malloc, free, 0, 16);
}
#endif 

static inline void turbolist_delete (turbolist *tl) {
    if(tl->next) tl->free(tl->next);
    if(tl->old) tl->free(tl->old);
}

static inline void turbolist_insert(turbolist *tl, int elem) {
    if(TL_LIKELY(tl->end < tl->capacity)) {
        bool hasmid = tl->mid > 0;
        tl->mid -= hasmid;

        tl->next[tl->mid] = hasmid ? tl->old[tl->mid] : tl->next[tl->mid];

        tl->next[tl->end++] = elem;
    } else {
        //grow
        __turbolist_grow_and_insert(tl, elem);
    }
}

static inline uint32_t turbolist_size(turbolist *tl) {
    return tl->mid + (tl->capacity - tl->end - 1);
}

#endif // TURBO_LIST_H