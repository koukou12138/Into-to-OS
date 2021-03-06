// Physical memory allocator, intended to allocate
// memory for user processes, kernel stacks, page table pages,
// and pipe buffers. Allocates 4096-byte pages.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"

void freerange(void *vstart, void *vend);

extern char end[]; // first address after kernel loaded from ELF file
// defined by the kernel linker script in kernel.ld

struct run {
    struct run *next;
};

struct frame {
    int pid;
    int frame;
}frame_table[16384];

int counter = 0;

struct {
    struct spinlock lock;
    int use_lock;
    struct run *freelist;
} kmem;


// Initialization happens in two phases.
// 1. main() calls kinit1() while still using entrypgdir to place just
// the pages mapped by entrypgdir on free list.
// 2. main() calls kinit2() with the rest of the physical pages
// after installing a full page table that maps them on all cores.
void
kinit1(void *vstart, void *vend) {
    initlock(&kmem.lock, "kmem");
    kmem.use_lock = 0;
    freerange(vstart, vend);
}

void
kinit2(void *vstart, void *vend) {
    freerange(vstart, vend);
    kmem.use_lock = 1;
}

void
freerange(void *vstart, void *vend) {
    char *p;
    p = (char *) PGROUNDUP((uint) vstart);
    for (; p + PGSIZE <= (char *) vend; p += PGSIZE) {
        kfree(p);
    }
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v) {
    struct run *r;

    if ((uint) v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
        panic("kfree");

    // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE);

    if (kmem.use_lock)
        acquire(&kmem.lock);

    r = (struct run *) v;
    r->next = kmem.freelist;
    kmem.freelist = r;
    if (kmem.use_lock)
        release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.

char *
kalloc(void) {
    struct run *r;

    if (kmem.use_lock)
        acquire(&kmem.lock);

    r = kmem.freelist;
    if (r) {//if the there's free page
        kmem.freelist = r->next->next; //leave a blank page
        if (kmem.use_lock && counter < 16384) {
            frame_table[counter].frame = (V2P(r) >> 12) & 0xffff;
            int free_frame_index = counter++;
            frame_table[free_frame_index].pid = -2;
        }
    }
    if (kmem.use_lock)
        release(&kmem.lock);
    return (char *) r;
}

char *
kalloc2(int pid) {
    struct run *r;

    if (kmem.use_lock)
        acquire(&kmem.lock);

    r = kmem.freelist;
    if (r) {//if the there's free page
        kmem.freelist = r->next->next; //leave a blank page
        if (kmem.use_lock && counter < 16384) {
            frame_table[counter].frame = (V2P(r) >> 12) & 0xffff;
            int free_frame_index = counter++;
            frame_table[free_frame_index].pid = pid;
        }
    }
    if (kmem.use_lock)
        release(&kmem.lock);
    return (char *) r;
}


int
dump_physmem(int *frames, int *pids, int numframes) {
    if (frames == 0) {
        return -1;
    }
    if (pids == 0) {
        return -1;
    }
    if (numframes == 0) {
        return -1;
    }

    if (kmem.use_lock)
        acquire(&kmem.lock);

    for (int i = 0; i < numframes; i++) {
        frames[i] = frame_table[i].frame;
        pids[i] = frame_table[i].pid;
    }

    if (kmem.use_lock)
        release(&kmem.lock);
    return 0;
}
