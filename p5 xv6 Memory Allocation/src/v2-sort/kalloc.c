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

struct frame_table_entry {
    int pid;
    struct run *frame;
} frame_table[16384];

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
    struct run *free_frame = kmem.freelist;
    for (int i = 0; i < 16384; i++) {
        frame_table[i].frame = free_frame;
        frame_table[i].pid = 0;
        free_frame = free_frame->next;
    }

    kmem.use_lock = 1;
}

void
free_frame(char *v) { //set a frame in free list(for init ONLY): linked list
    struct run *r;

    if ((uint) v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
        panic("kfree");

    // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE);

    if (kmem.use_lock)
        acquire(&kmem.lock);

    // insert new freed page at FRONT of freelist
    r = (struct run *) v;
    r->next = kmem.freelist;
    kmem.freelist = r;

    if (kmem.use_lock)
        release(&kmem.lock);
}

void
freerange(void *vstart, void *vend) {
    char *p;
    p = (char *) PGROUNDUP((uint) vstart);
    for (; p + PGSIZE <= (char *) vend; p += PGSIZE) {
        free_frame(p);
    }
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v) {

    if ((uint) v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
        panic("kfree");

    // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE);

    if (kmem.use_lock)
        acquire(&kmem.lock);

    for (int i = 0; i < 16384; i++) {
        if (frame_table[i].frame == (struct run *) v) {
            frame_table[i].pid = 0;
            break;
        }
    }

    if (kmem.use_lock)
        release(&kmem.lock);
}


int
checkleft(int i, int pid) {
    return (frame_table[i - 1].pid == pid || frame_table[i - 1].pid == 0
            || frame_table[i - 1].pid == -2);
}

int
checkright(int i, int pid) {
    return (frame_table[i + 1].pid == pid || frame_table[i + 1].pid == 0
            || frame_table[i + 1].pid == -2);
}

struct run *
getframe(int pid) {
    if (frame_table[0].pid == 0
        && (frame_table[1].pid == 0 || frame_table[1].pid == pid)) {
        frame_table[0].pid = pid;
        return frame_table[0].frame;
    }

    for (int i = 1; i < 16384; i++) {
        if (pid == -2 && frame_table[i].pid == 0) {
            frame_table[i].pid = pid;
            return frame_table[i].frame;
        }
        if (checkleft(i, pid) && checkright(i, pid) && frame_table[i].pid == 0) {
            frame_table[i].pid = pid;
            return frame_table[i].frame;
        }
    }
    return 0;
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char *
kalloc(void) {
    struct run *r;
    if (kmem.use_lock)
        acquire(&kmem.lock);
    if (!kmem.use_lock) {
        r = kmem.freelist;
        if (r) {
            kmem.freelist = r->next;
        }
    } else {
        r = getframe(-2);
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
    if (!kmem.use_lock) {
        r = kmem.freelist;
        if (r) {
            kmem.freelist = r->next;
        }
    } else {
        r = getframe(pid);
    }
    if (kmem.use_lock)
        release(&kmem.lock);
    return (char *) r;
}

int dump_physmem(int *frames, int *pids, int numframes) {
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

    int counter = 0;
    for (int i = 0; counter < numframes; i++) {
        if (frame_table[i].pid != 0) {
            frames[counter] = (V2P(frame_table[i].frame) >> 12) & 0xffff;
            pids[counter++] = frame_table[i].pid;
        }
    }

    if (kmem.use_lock)
        release(&kmem.lock);
    return 0;
}