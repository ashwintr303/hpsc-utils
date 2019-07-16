#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/* This SRAM test will either print or modify the contents of SRAM.  In both
 * cases, SRAM will be mapped into memory using mmap and later unmapped using
 * munmap. */

/* CHECK THE DEVICE TREE TO SEE IF HPPS SRAM ADDRESS HAS CHANGED TO 0x600000000 */
#define HPPS_SRAM0_ADDR 0x680000000
#define NUM_INTS_PER_LINE 30
#define MODIFY_SRAM 0
#define PRINT_SRAM 1

/* RETURN CODES */
#define SUCCESS 0
#define INVALID_PARAMETER 1
#define FILE_WRITE_ERROR 2
#define FILE_MMAP_ERROR 3
#define FILE_UNMMAP_ERROR 4

// modify_or_print_sram dictates whether SRAM contents are modified or merely printed
int modify_or_print_sram;
// num_ints is the number of ints in the mapped file
int num_ints;

void print_params() {
    printf("\n");
    if (modify_or_print_sram == MODIFY_SRAM) {
        printf("SRAM contents will be modified.\n");
    }
    else if (modify_or_print_sram == PRINT_SRAM) {
        printf("SRAM contents will be printed.\n");
    }

    printf("filesize (in ints): %d\n", num_ints);
}

void print_array(int *arr) {
    int i;

    for (i = 0; i < num_ints; i++) {
        printf("%d, ", arr[i]);
        if ((i > 0) && (i % NUM_INTS_PER_LINE == 0)) printf("\n");
    }
    printf("\n");
}

/* Arbitrarily change the contents of arr */
void modify_array(int *arr) {
    int i;

    for (i = 0; i < num_ints; i++) {
        arr[i] = arr[i]+1;
    }
}

/*  If we are modifying SRAM, then arr will be updated to contain
 *  the new contents of SRAM.  Otherwise, print the SRAM contents */ 
int access_sram() {
    int i;
    int fd;
    int file_size;
    int *map;  /* mmapped array of ints */

   /* Open a file for writing.
    *  - Creating the file if it doesn't exist.
    *  - Truncating it to 0 size if it already exists. (not really needed)
    *
    * Note: "O_WRONLY" mode is not sufficient when mmaping.
    */
    fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
        return FILE_WRITE_ERROR;
    }

    file_size = num_ints * sizeof(int);
    map = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, HPPS_SRAM0_ADDR);
    if (map == MAP_FAILED) {
        close(fd);
	return FILE_MMAP_ERROR;
    }

    if (modify_or_print_sram == MODIFY_SRAM) {
	/* Modify the array to see if the changes are visible later. */
	modify_array(map);
    }
    else if (modify_or_print_sram == PRINT_SRAM) {
	printf("Current SRAM contents:\n");
	print_array(map);
    }

    /* Now free the mmapped memory */
    if (munmap(map, file_size) == -1) {
	return FILE_UNMMAP_ERROR;
    }

    /* Un-mmaping doesn't close the file, so we do that now. */
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    int c, ret;

    // set parameter default values
    modify_or_print_sram = PRINT_SRAM;
    num_ints = 1000;

    while ((c = getopt(argc, argv, "f:s:")) != -1) {
	switch(c) {
	    case 'f':
		num_ints = atoi(optarg);
                break;
	    case 's':
		if (optarg[0] == 'm') {
		    modify_or_print_sram = MODIFY_SRAM;
		}
		else if (optarg[0] == 'p') {
		    modify_or_print_sram = PRINT_SRAM;
		}
		else {
		    printf("unknown option: %c\n", optarg[0]);
		    return INVALID_PARAMETER;
		}
		break; 
            case '?':
                printf("unknown option: %c\n", optopt); 
                return INVALID_PARAMETER;
        }
    }
    print_params();

    ret = access_sram();
    if (ret != 0) {
	return ret;
    }
    return SUCCESS;
}
