#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <ctype.h>
#include "fs.h"

char bitarr[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
#define BITSET(bitmap, blockaddr) ((*(bitmap + blockaddr / 8)) & (bitarr[blockaddr % 8])) 

void *base_ptr;
struct superblock *super_block;

int count_direct_datablocks(struct dinode *inode) {
    int i;
    int count = 0;
    for (i = 0; i < NDIRECT; i++) {
        if (inode->addrs[i] != 0) {
          count++;
        }
    }
    return count;
}

int count_indirect_datablocks( struct dinode *inode) {
    uint *indirect_block;
    int i;
    int count = 0;
    if (inode->addrs[NDIRECT] == 0) {
      return 0;
    }
    indirect_block = (uint *) (base_ptr + inode->addrs[NDIRECT] * BSIZE);
    for (i = 0; i < NINDIRECT; i++) {
        if (*indirect_block != 0) {
          count++;
        }
        indirect_block++;
    }
    return count;
}


void inode_checks() {
  int i;
  struct dinode *inode;
  inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart);
  for (i = 0; i < super_block->ninodes; i++, inode++) {
    if (inode -> type < 0 || inode -> type > 3) {
      fprintf(stderr,"ERROR: bad inode.\n");
      exit(1);
    }
    if (inode -> type == 0) {
      continue;
    }

    int valid_data_blocks = count_direct_datablocks(inode) + count_indirect_datablocks(inode);
    
    if ((int) (valid_data_blocks) * BSIZE < (int)inode -> size || (int)((valid_data_blocks - 1) * BSIZE) >= (int) inode -> size) {
      fprintf(stderr,"ERROR: bad size in inode.\n");
      exit(1);
    }
  }
}

void directory_checks() {
  int i;
  struct dinode *root_dir;
  //printf("%ld\n", sizeof(struct dinode));
  //printf("%ld\n", (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart));
  root_dir = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart) + 1;
  //printf("%ld\n", root_dir);
  //printf("%d\n", root_dir -> type);
  if (root_dir -> type != 1) {
    fprintf(stderr,"ERROR: root directory does not exist.\n");
    exit(1);
  }

  struct dirent* dir = base_ptr + (BSIZE*root_dir->addrs[0]);
  if (dir->inum == 1){
    if ((dir+1)->inum != 1) {
      fprintf(stderr,"ERROR: root directory does not exist.\n");
      exit(1);
    }
  }

  struct dinode *inode;
  inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart);
  for (i = 0; i < super_block->ninodes; i++, inode++) {
    if (inode -> type == 0) {
      continue;
    }

    if (inode -> type == 1) {
      //int dotadr = inode[i]->addrs[0];
      struct dirent *dot_dir = (struct dirent *) (base_ptr + inode -> addrs[0] * BSIZE);
      if (dot_dir -> inum != i) {
        fprintf(stderr,"ERROR: current directory mismatch.\n");
        exit(1);
      }
    }
  }
}

void bitmap_checks() {
  int i, j;
  int data_blocks[super_block -> size];
  struct dinode *inode;
  inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart);
  for (i = 0; i < super_block->size; i++) {
    data_blocks[i] = -1;
  }
  for (i = 0; i < super_block->ninodes; i++, inode++) {
    if (inode -> type == 0) {
      continue;
    }
    for (j = 0; j < NDIRECT; j++) {
      if (inode->addrs[j] == 0) {
        continue;
      }
      //printf("%d\n", inode->addrs[j]);
      data_blocks[inode->addrs[j]] = 1;
    }
    if (inode->addrs[NDIRECT] != 0) {
      data_blocks[inode->addrs[NDIRECT]] = 1;
      uint *indirect_blocks = (uint *) (base_ptr + inode->addrs[NDIRECT] * BSIZE);
      for (j = 0; j < NINDIRECT; j++, indirect_blocks++) {
          if (*indirect_blocks == 0) {
            continue;
          }
          //printf("%d\n", *indirect_blocks);
          data_blocks[*indirect_blocks] = 1;
      }
    }
  }
  char *bitmap;
  bitmap = (char *) (base_ptr + BSIZE*super_block -> bmapstart);
  for (i = (super_block->bmapstart + 1); i < super_block->size; i++) {
        if (data_blocks[i] == -1 && BITSET(bitmap, (uint) i)) {
          //printf("%d\n", i);
          fprintf(stderr,"ERROR: bitmap marks data block in use but not used.\n");
          exit(1);
        }
        if (data_blocks[i] == 1 && !BITSET(bitmap, (uint) i)) {
          fprintf(stderr,"ERROR: bitmap marks data free but data block used by inode.\n");
          exit(1);
        }
  }
}

void multistructure_checks() {
  int i, j, k;
  int is_referred[super_block->ninodes];
  struct dinode *inode;
  inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart);
  for (i = 0; i < super_block->ninodes; i++, inode++) {
    if (inode -> type == 1) {
      int finished = 0;
      for (j = 0; j < NDIRECT; j++) {
          struct dirent *dir = (struct  dirent *) (base_ptr + inode->addrs[j] * BSIZE);
          for (k=0; k < BSIZE / sizeof(struct dirent *); k++, dir++) {
            struct dinode *another_inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart) + dir -> inum;
            if (dir -> inum != 0 && another_inode -> type == 0) {
              fprintf(stderr,"ERROR: inode marked free but referred to in directory.\n");
              exit(1);
            }
            if (dir -> inum != 0) {
                is_referred[dir -> inum] = 1;
            } else {
                finished = 1;
                break;
            }
          }
          if (finished) {
              break;
          }
      }
    }
  }
  inode = (struct dinode *) (base_ptr + BSIZE * super_block -> inodestart);
  for (i = 0; i < super_block->ninodes; i++, inode++) {
    if (inode -> type != 0) {
      if (is_referred[i] != 1) {
        fprintf(stderr,"ERROR: inode marked in use but not found in a directory.\n");
        exit(1);
      }
    }
  }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    } 
    int fd;
    fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0) {
        exit(1);
    }
    struct stat Statbuffer;
    if (fstat(fd, &Statbuffer) != 0) {
        exit(1);
    }
    base_ptr = mmap(NULL,Statbuffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (base_ptr == MAP_FAILED) { 
        exit(1);
    }

    super_block = (struct superblock *) (base_ptr + BSIZE);
    
    inode_checks();
    directory_checks();
    bitmap_checks();
    multistructure_checks();

    munmap(base_ptr, Statbuffer.st_size);
	  close(fd);
    return 0;
}   