#include <stdio.h>

enum {FILE_SYSTEM_SIZE = 1048576,
INODE_SIZE = 13};

struct inode{
    unsigned file_size;
    long int num_block_files[INODE_SIZE];
};

struct system{
    unsigned root_num;
    struct inode arr_inode[FILE_SYSTEM_SIZE];
} file_system;

int
main(void){
    file_system.arr_inode[10].file_size = 2 * sizeof(file_system.arr_inode[0]);
    file_system.arr_inode[10].num_block_files[0] = 1038;
    file_system.arr_inode[10].num_block_files[1] = 37465;
    return 0;
}
