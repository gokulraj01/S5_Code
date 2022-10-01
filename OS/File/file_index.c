#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LINE_LEN 10
#define INDEX_LEN 128

// Make a random int from min to max-1
int randint(int min, int max){
    int r = rand();
    return r%(max-min)+min;
}

void main(){
    // Seed time to pseudo-rand generator
    srand(time(0));

    // Input parameters
    int memSize, blkSize, fileSize;
    printf("Total Mem Size: ");
    scanf("%d", &memSize);
    printf("Block Size: ");
    scanf("%d", &blkSize);
    printf("File Size: ");
    scanf("%d", &fileSize);
    
    // Find block size and allocate in memory
    int blks = ceil(memSize/blkSize);
    char *allocList = malloc(blks);
    int i = 0;
    while(i < blks)
        allocList[i++] = 0;
    
    // Store indices
    int *indices = malloc(4*INDEX_LEN);
    
    // Allocate the blocks for file.
    int file_blk = ceil(fileSize/blkSize);
    int ctr = 0; i = 0;
    printf("Indices: ");
    while(i < blks && ctr < file_blk){
        // Pick a random block to use
        int i = randint(0, blks);
        // If not allocated...
        if(allocList[i] == 0){
            allocList[i] = 1;   // Mark as allocated
            indices[ctr++] = i;   // Store index
            printf("%d ", i);
        }
        i++;
    }
    putchar('\n');
    
    // Check allocation status
	if(ctr < file_blk)
		printf("Cannot allocate!!\n");
	else
		printf("Allocation complete!!\n");
	
    // Display allocation
    printf("\n%d blocks, %db each. Size: %db\n", blks, blkSize, blks*blkSize);
	printf("\nAllocations");
	for(i=0; i<blks; i++){
	    if(i%LINE_LEN == 0)
	        putchar('\n');
	    if(allocList[i])
		    printf("X ");
	    else
		    printf(". ");
	}
	putchar('\n');
}
