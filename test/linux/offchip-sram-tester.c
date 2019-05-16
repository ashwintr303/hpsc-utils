
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILEPATH "/tmp/mmapped.bin"
#define NUMINTS  (100)
#define FILESIZE (NUMINTS * sizeof(int))

int main()
{
    int i, error;
    int fd;
    int *map;  /* mmapped array of int's */
    int buf[NUMINTS];

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
	perror("Error opening file for writing");
	exit(EXIT_FAILURE);
    }
    printf("open /dev/mem is fine\n");

    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x600000000);
    if (map == MAP_FAILED) {
	close(fd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }
    printf("after mmap\n");
   
    /* Now write int's to the file as if it were memory (an array of ints).
     */
 
    printf(" ----- Original SRAM content -----");
    for (i = 0; i < NUMINTS; ++i) {
        if (i % 64 == 0) printf("\n");
        printf("%d, ", map[i]);
        buf[i] = map[i];
    }
    printf("\n");

    for (i = 0; i < NUMINTS; ++i) {
	map[i] = map[i]+1;
    }

    printf("after memcpy\n");
    printf(" ----- New SRAM content -----");
    for (i = error = 0; i < NUMINTS; ++i) {
        if (i % 64 == 0) printf("\n");
        printf("%d, ", map[i]);
        if (buf[i] + 1 != map[i]) error++;
    }
    printf("\n");

    if (error)
        printf("FAIL: there are %d errors\n", error);
    else
        printf("SUCCESS\n");
    /* Don't forget to free the mmapped memory
     */
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
	/* Decide here whether to close(fd) and exit() or not. Depends... */
    }

    /* Un-mmaping doesn't close the file, so we still need to do that.
     */
    close(fd);
    return 0;
}


